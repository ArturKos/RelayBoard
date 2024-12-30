#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "crc.h"
#include "main.h"

unsigned char message_to_board[MESSAGE_TO_BOARD_LENGTH] = {0x55,0x01,'S',0xff,0x28};
char config[MAX_RELAY][MAX_RELAY_NAME_LENGTH] = {{0}};

/**
 * @brief Reads the configuration file.
 * 
 * @return true if the configuration file was read successfully, false otherwise.
 */
static bool read_config_file() {
	FILE *config_file = fopen(POWER_STRIP_CONFIG_FILE_NAME, "r+");
	if (NULL == config_file) {
		return false;
	}
	int idx = 0;
	while (fgets(config[idx], MAX_RELAY_NAME_LENGTH, config_file) && idx < MAX_RELAY_IDX + 1) {
		if (strlen(config[idx]) > 0) {
			config[idx][strlen(config[idx]) - 1] = 0;
		}
		idx++;
	}
	fclose(config_file);
	return true;
}

/**
 * @brief Sets up the board.
 */
static void board_setup() {
	char setup_device_command[SETUP_DEVICE_COMMAND_BUF_LEN] = {0};
	sprintf(setup_device_command, "stty -F %s 57600 cs8 -cstopb -parity -icanon min 100 time 1", (char *)config[DEVICE_IDX]);
	system(setup_device_command);
}

/**
 * @brief Gets the status of the relays from the board.
 * 
 * @return true if the status was retrieved successfully, false otherwise.
 */
static bool board_get_relays_status() {
	unsigned char reply_message_from_board[MESSAGE_TO_BOARD_LENGTH] = {0};

	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = RELAYS_MESSAGE_ALL_ON;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_GET_STATUS;
	message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

	FILE *board = fopen((char *)config[DEVICE_IDX], "r+");
	if (NULL == board) {
		return false;
	}
	if (MESSAGE_TO_BOARD_LENGTH != fwrite(message_to_board, sizeof(char), MESSAGE_TO_BOARD_LENGTH, board)) {
		fclose(board);
		return false;
	}

	// Add a delay between writing and reading
	usleep(100000); // 100 milliseconds

	if (MESSAGE_TO_BOARD_LENGTH != fread(reply_message_from_board, sizeof(char), MESSAGE_TO_BOARD_LENGTH, board)) {
		fclose(board);
		return false;
	}

	for (int relay_idx = 0; relay_idx <= MAX_RELAY_IDX; relay_idx++) {
		if (reply_message_from_board[RELAYS_MESSAGE_RELAY_INDEX] & (1 << relay_idx))
			printf("Relay %d is on  - %s\n", relay_idx + 1, config[relay_idx + 1]);
		else
			printf("Relay %d is off - %s\n", relay_idx + 1, config[relay_idx + 1]);
	}
	fclose(board);
	return true;
}

/**
 * @brief Writes a message to the board.
 * 
 * @return true if the message was written successfully, false otherwise.
 */
static bool board_write_message_to_board() {
	FILE *board = fopen((char *)config[DEVICE_IDX], "r+");
	if (NULL == board) {
		return false;
	}
	if (MESSAGE_TO_BOARD_LENGTH != fwrite(message_to_board, sizeof(char), MESSAGE_TO_BOARD_LENGTH, board)) {
		fclose(board);
		return false;
	}
	fclose(board);
	return true;
}

/**
 * @brief Switches all relays on.
 * 
 * @return true if the relays were switched on successfully, false otherwise.
 */
static bool board_switch_all_on() {
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = RELAYS_MESSAGE_ALL_ON;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_SET_STATUS;
	message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

	return board_write_message_to_board();
}

/**
 * @brief Switches all relays off.
 * 
 * @return true if the relays were switched off successfully, false otherwise.
 */
static bool board_switch_all_off() {
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = RELAYS_MESSAGE_ALL_OFF;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_SET_STATUS;
	message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

	return board_write_message_to_board();
}

/**
 * @brief Switches a specific relay on.
 * 
 * @param relay_number The relay number to switch on.
 * @return true if the relay was switched on successfully, false otherwise.
 */
static bool board_switch_on(unsigned char relay_number) {
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = relay_number;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_ON;
	message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

	return board_write_message_to_board();
}

/**
 * @brief Switches a specific relay off.
 * 
 * @param relay_number The relay number to switch off.
 * @return true if the relay was switched off successfully, false otherwise.
 */
static bool board_switch_off(unsigned char relay_number) {
	message_to_board[RELAYS_MESSAGE_RELAY_INDEX] = relay_number;
	message_to_board[RELAYS_MESSAGE_OPTION_INDEX] = RELAY_OFF;
	message_to_board[RELAYS_MESSAGE_CRC_INDEX] = CountCRC(message_to_board);

	return board_write_message_to_board();
}

/**
 * @brief Prints the usage message.
 */
static void print_usage_message() {
	printf("Usage:\n");
	printf("1. power_strip status\n");
	printf("2. power_strip allon\n");
	printf("3. power_strip alloff\n");
	printf("4. power_strip X on  (X - relay number from 1 to 8)\n");
	printf("5. power_strip X off (X - relay number from 1 to 8)\n");
}

int main(int argc, char *argv[]) {
	if (!read_config_file()) {
		printf("Error loading config file: %s\n", POWER_STRIP_CONFIG_FILE_NAME);
		return -1;
	}

	if (argc != 2 && argc != 3) {
		print_usage_message();
		return -1;
	}

	board_setup();

	if (argc == 2) {
		if (0 == strcmp(argv[1], "allon")) {
			if (board_switch_all_on()) {
				printf("Switched all relays on\n");
				return 0;
			} else {
				printf("Error switching all relays to on\n");
				return 1;
			}
		}
		if (0 == strcmp(argv[1], "alloff")) {
			if (board_switch_all_off()) {
				printf("Switched all relays off\n");
				return 0;
			} else {
				printf("Error switching all relays to off\n");
				return 1;
			}
		}
		if (0 == strcmp(argv[1], "status")) {
			if (board_get_relays_status()) {
				return 0;
			} else {
				printf("Error getting status of relays\n");
				return 1;
			}
		}
	}

	if (argc == 3) {
		int switch_idx = atoi(argv[1]);
		if (0 == switch_idx || ((switch_idx - 1) < MIN_RELAY_IDX) || ((switch_idx - 1) > MAX_RELAY_IDX)) {
			print_usage_message();
			return -1;
		}
		if (0 == strcmp(argv[2], "on")) {
			if (board_switch_on(switch_idx - 1)) {
				printf("Switched relay on - %s\n", config[switch_idx]);
				return 0;
			} else {
				print_usage_message();
				return -1;
			}
		}
		if (0 == strcmp(argv[2], "off")) {
			if (board_switch_off(switch_idx - 1)) {
				printf("Switched relay off - %s\n", config[switch_idx]);
				return 0;
			} else {
				print_usage_message();
				return -1;
			}
		}
	}

	print_usage_message();
	return -1;
}