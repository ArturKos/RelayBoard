/**
 * @file main.c
 * @brief Command-line driver for an 8-channel serial relay board.
 *
 * Reads the serial device path and relay labels from a config file,
 * talks to the board over 57600 8N1 using a 5-byte framed protocol
 * with CRC8, and persists the latest relay bitmask to a state file so
 * it can be restored after a power loss.
 */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "crc.h"
#include "main.h"

/**
 * @brief Line 0 holds the serial device path, lines 1..8 hold
 *        human-readable names for relays 1..8.
 */
static char config[MAX_RELAY][MAX_RELAY_NAME_LENGTH];

/**
 * @brief Loads #POWER_STRIP_CONFIG_FILE_NAME from the working directory
 *        into the ::config table and strips trailing CR/LF on each line.
 *
 * @return true on success; false if the file cannot be opened or contains
 *         fewer than #MAX_RELAY lines.
 */
static bool read_config_file(void) {
	FILE *f = fopen(POWER_STRIP_CONFIG_FILE_NAME, "r");
	if (!f) {
		fprintf(stderr, "Cannot open config '%s': %s\n",
		        POWER_STRIP_CONFIG_FILE_NAME, strerror(errno));
		return false;
	}
	int idx = 0;
	while (idx < MAX_RELAY && fgets(config[idx], MAX_RELAY_NAME_LENGTH, f)) {
		size_t n = strlen(config[idx]);
		while (n > 0 && (config[idx][n - 1] == '\n' || config[idx][n - 1] == '\r')) {
			config[idx][--n] = '\0';
		}
		idx++;
	}
	fclose(f);
	if (idx < MAX_RELAY) {
		fprintf(stderr, "Config '%s' has only %d lines, expected %d\n",
		        POWER_STRIP_CONFIG_FILE_NAME, idx, MAX_RELAY);
		return false;
	}
	return true;
}

/**
 * @brief Opens the serial device named in config[#DEVICE_IDX] and
 *        configures it for 57600 8N1, raw mode, with a blocking read
 *        timeout of #SERIAL_READ_TIMEOUT_DECISECONDS tenths of a second.
 *
 * @return An open, configured file descriptor on success, or -1 on error.
 */
static int board_open(void) {
	int fd = open(config[DEVICE_IDX], O_RDWR | O_NOCTTY);
	if (fd < 0) {
		fprintf(stderr, "Cannot open '%s': %s\n",
		        config[DEVICE_IDX], strerror(errno));
		return -1;
	}
	struct termios tio;
	if (tcgetattr(fd, &tio) != 0) {
		fprintf(stderr, "tcgetattr failed: %s\n", strerror(errno));
		close(fd);
		return -1;
	}
	cfmakeraw(&tio);
	cfsetispeed(&tio, B57600);
	cfsetospeed(&tio, B57600);
	tio.c_cflag |= (CLOCAL | CREAD);
	tio.c_cflag &= ~(unsigned)CSTOPB;
	tio.c_cflag &= ~(unsigned)PARENB;
	tio.c_cflag = (tio.c_cflag & ~(unsigned)CSIZE) | CS8;
	tio.c_cc[VMIN]  = 0;
	tio.c_cc[VTIME] = SERIAL_READ_TIMEOUT_DECISECONDS;
	if (tcsetattr(fd, TCSANOW, &tio) != 0) {
		fprintf(stderr, "tcsetattr failed: %s\n", strerror(errno));
		close(fd);
		return -1;
	}
	tcflush(fd, TCIOFLUSH);
	return fd;
}

/**
 * @brief Fills a 5-byte protocol frame with sync/address/cmd/data and
 *        the matching CRC8.
 *
 * @param frame Output buffer of exactly #MESSAGE_LENGTH bytes.
 * @param cmd   Command byte (#CMD_SET_STATUS, #CMD_GET_STATUS, ...).
 * @param data  Payload byte (bitmask for SET/GET, relay index for ON/OFF).
 */
static void build_frame(uint8_t *frame, uint8_t cmd, uint8_t data) {
	frame[MSG_SYNC_INDEX] = FRAME_SYNC_BYTE;
	frame[MSG_ADDR_INDEX] = FRAME_DEVICE_ADDR;
	frame[MSG_CMD_INDEX]  = cmd;
	frame[MSG_DATA_INDEX] = data;
	frame[MSG_CRC_INDEX]  = CountCRC(frame);
}

/**
 * @brief Builds and writes one framed command to the board, retrying
 *        on EINTR and draining the TX buffer before returning.
 *
 * @param fd   Open serial descriptor from board_open().
 * @param cmd  Command byte.
 * @param data Payload byte.
 * @return true on success, false on I/O error.
 */
static bool board_write_frame(int fd, uint8_t cmd, uint8_t data) {
	uint8_t frame[MESSAGE_LENGTH];
	build_frame(frame, cmd, data);
	size_t sent = 0;
	while (sent < MESSAGE_LENGTH) {
		ssize_t n = write(fd, frame + sent, MESSAGE_LENGTH - sent);
		if (n < 0) {
			if (errno == EINTR) continue;
			fprintf(stderr, "Serial write failed: %s\n", strerror(errno));
			return false;
		}
		sent += (size_t)n;
	}
	tcdrain(fd);
	return true;
}

/**
 * @brief Reads exactly #MESSAGE_LENGTH bytes of a reply frame and
 *        validates sync, address, command (#CMD_REPLY) and CRC8.
 *
 * @param fd       Open serial descriptor.
 * @param data_out Receives the data byte from a well-formed reply.
 * @return true if a valid reply was received, false on timeout or
 *         protocol/CRC error.
 */
static bool board_read_reply(int fd, uint8_t *data_out) {
	uint8_t frame[MESSAGE_LENGTH];
	size_t got = 0;
	while (got < MESSAGE_LENGTH) {
		ssize_t n = read(fd, frame + got, MESSAGE_LENGTH - got);
		if (n < 0) {
			if (errno == EINTR) continue;
			fprintf(stderr, "Serial read failed: %s\n", strerror(errno));
			return false;
		}
		if (n == 0) {
			fprintf(stderr, "Serial read timeout (got %zu/%d bytes)\n",
			        got, MESSAGE_LENGTH);
			return false;
		}
		got += (size_t)n;
	}
	if (frame[MSG_SYNC_INDEX] != FRAME_SYNC_BYTE) {
		fprintf(stderr, "Bad sync byte in reply: 0x%02x\n", frame[MSG_SYNC_INDEX]);
		return false;
	}
	if (frame[MSG_ADDR_INDEX] != FRAME_DEVICE_ADDR) {
		fprintf(stderr, "Bad device address in reply: 0x%02x\n", frame[MSG_ADDR_INDEX]);
		return false;
	}
	if (frame[MSG_CMD_INDEX] != CMD_REPLY) {
		fprintf(stderr, "Unexpected reply command: 0x%02x\n", frame[MSG_CMD_INDEX]);
		return false;
	}
	if (frame[MSG_CRC_INDEX] != CountCRC(frame)) {
		fprintf(stderr, "CRC mismatch in reply\n");
		return false;
	}
	*data_out = frame[MSG_DATA_INDEX];
	return true;
}

/**
 * @brief Sends #CMD_GET_STATUS and returns the board's relay bitmask.
 *
 * @param fd        Open serial descriptor.
 * @param state_out Receives the 8-bit bitmask (bit i = relay i+1 on).
 * @return true on success.
 */
static bool board_get_status(int fd, uint8_t *state_out) {
	if (!board_write_frame(fd, CMD_GET_STATUS, 0x00)) return false;
	return board_read_reply(fd, state_out);
}

/**
 * @brief Sends #CMD_SET_STATUS with a full relay bitmask.
 *
 * @param fd    Open serial descriptor.
 * @param state Bitmask to apply (bit i controls relay i+1).
 * @return true on success.
 */
static bool board_set_state(int fd, uint8_t state) {
	return board_write_frame(fd, CMD_SET_STATUS, state);
}

/**
 * @brief Persists the current relay bitmask to #POWER_STRIP_STATE_FILE_NAME
 *        so it can be reapplied after a power loss via `restore`.
 *
 * @param state Bitmask to save.
 * @return true if the file was written; false is non-fatal and only warns.
 */
static bool save_state(uint8_t state) {
	FILE *f = fopen(POWER_STRIP_STATE_FILE_NAME, "w");
	if (!f) {
		fprintf(stderr, "Warning: cannot save state to '%s': %s\n",
		        POWER_STRIP_STATE_FILE_NAME, strerror(errno));
		return false;
	}
	fprintf(f, "0x%02x\n", state);
	fclose(f);
	return true;
}

/**
 * @brief Reads a previously saved bitmask from #POWER_STRIP_STATE_FILE_NAME.
 *
 * @param state_out Receives the loaded bitmask on success.
 * @return true on success; false if the file is missing or malformed.
 */
static bool load_state(uint8_t *state_out) {
	FILE *f = fopen(POWER_STRIP_STATE_FILE_NAME, "r");
	if (!f) {
		fprintf(stderr, "Cannot open state file '%s': %s\n",
		        POWER_STRIP_STATE_FILE_NAME, strerror(errno));
		return false;
	}
	unsigned int v = 0;
	int matched = fscanf(f, "%x", &v);
	fclose(f);
	if (matched != 1 || v > 0xff) {
		fprintf(stderr, "Invalid content in state file '%s'\n",
		        POWER_STRIP_STATE_FILE_NAME);
		return false;
	}
	*state_out = (uint8_t)v;
	return true;
}

/**
 * @brief Prints a one-line status for each relay using its config label.
 *
 * @param state Bitmask describing the current relay outputs.
 */
static void print_state(uint8_t state) {
	for (int i = MIN_RELAY_IDX; i <= MAX_RELAY_IDX; i++) {
		const char *label = (state & (uint8_t)(1u << i)) ? "on " : "off";
		printf("Relay %d is %s - %s\n", i + 1, label, config[i + 1]);
	}
}

/**
 * @brief Prints the CLI usage banner to stdout.
 *
 * @param prog Program name (typically argv[0]).
 */
static void print_usage(const char *prog) {
	printf("Usage:\n");
	printf("  %s status        query and show relay states\n", prog);
	printf("  %s allon         switch all relays on\n", prog);
	printf("  %s alloff        switch all relays off\n", prog);
	printf("  %s N on          switch relay N (1..8) on\n", prog);
	printf("  %s N off         switch relay N (1..8) off\n", prog);
	printf("  %s restore       restore state saved in '%s'\n",
	       prog, POWER_STRIP_STATE_FILE_NAME);
}

/**
 * @brief Parses a decimal relay number from a string, accepting only 1..8.
 *
 * @param s Input string.
 * @return Relay number in [1, 8] on success, -1 on any parse error.
 */
static int parse_relay_number(const char *s) {
	char *end = NULL;
	long n = strtol(s, &end, 10);
	if (end == s || *end != '\0') return -1;
	if (n < 1 || n > 8) return -1;
	return (int)n;
}

/**
 * @brief Program entry point: parses the sub-command, talks to the board
 *        and updates the state file on every successful change.
 *
 * @param argc Standard argument count.
 * @param argv Standard argument vector.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on any error.
 */
int main(int argc, char *argv[]) {
	if (!read_config_file()) return EXIT_FAILURE;

	if (argc != 2 && argc != 3) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	int fd = board_open();
	if (fd < 0) return EXIT_FAILURE;

	int rc = EXIT_FAILURE;

	if (argc == 2) {
		if (strcmp(argv[1], "status") == 0) {
			uint8_t state;
			if (board_get_status(fd, &state)) {
				print_state(state);
				save_state(state);
				rc = EXIT_SUCCESS;
			} else {
				fprintf(stderr, "Error getting status from board\n");
			}
		} else if (strcmp(argv[1], "allon") == 0) {
			if (board_set_state(fd, RELAYS_ALL_ON)) {
				save_state(RELAYS_ALL_ON);
				printf("Switched all relays on\n");
				rc = EXIT_SUCCESS;
			} else {
				fprintf(stderr, "Error switching relays on\n");
			}
		} else if (strcmp(argv[1], "alloff") == 0) {
			if (board_set_state(fd, RELAYS_ALL_OFF)) {
				save_state(RELAYS_ALL_OFF);
				printf("Switched all relays off\n");
				rc = EXIT_SUCCESS;
			} else {
				fprintf(stderr, "Error switching relays off\n");
			}
		} else if (strcmp(argv[1], "restore") == 0) {
			uint8_t state;
			if (load_state(&state) && board_set_state(fd, state)) {
				printf("Restored relay state 0x%02x\n", state);
				print_state(state);
				rc = EXIT_SUCCESS;
			} else {
				fprintf(stderr, "Error restoring relay state\n");
			}
		} else {
			print_usage(argv[0]);
		}
	} else {
		int n = parse_relay_number(argv[1]);
		if (n < 0) {
			print_usage(argv[0]);
		} else {
			uint8_t current;
			uint8_t mask = (uint8_t)(1u << (n - 1));
			if (!board_get_status(fd, &current)) {
				fprintf(stderr, "Error querying current state\n");
			} else if (strcmp(argv[2], "on") == 0) {
				uint8_t next = (uint8_t)(current | mask);
				if (board_set_state(fd, next)) {
					save_state(next);
					printf("Switched relay %d on - %s\n", n, config[n]);
					rc = EXIT_SUCCESS;
				} else {
					fprintf(stderr, "Error switching relay %d on\n", n);
				}
			} else if (strcmp(argv[2], "off") == 0) {
				uint8_t next = (uint8_t)(current & (uint8_t)~mask);
				if (board_set_state(fd, next)) {
					save_state(next);
					printf("Switched relay %d off - %s\n", n, config[n]);
					rc = EXIT_SUCCESS;
				} else {
					fprintf(stderr, "Error switching relay %d off\n", n);
				}
			} else {
				print_usage(argv[0]);
			}
		}
	}

	close(fd);
	return rc;
}
