/**
 * @file main.h
 * @brief Protocol constants, frame layout and configuration paths
 *        shared between the CLI driver and helpers.
 */

#ifndef MAIN_BOARD_H
#define MAIN_BOARD_H

#define POWER_STRIP_CONFIG_FILE_NAME "power_strip.conf"
#define POWER_STRIP_STATE_FILE_NAME  "power_strip.state"

#define MESSAGE_LENGTH 5
#define MAX_RELAY 9 /* device path at line 0, 8 relay names at lines 1..8 */
#define MAX_RELAY_NAME_LENGTH 50

#define DEVICE_IDX 0
#define MIN_RELAY_IDX 0
#define MAX_RELAY_IDX 7

#define FRAME_SYNC_BYTE    0x55
#define FRAME_DEVICE_ADDR  0x01

#define CMD_SET_STATUS 'S'
#define CMD_RELAY_ON   'O'
#define CMD_RELAY_OFF  'F'
#define CMD_GET_STATUS 'G'
#define CMD_REPLY      'R'

#define MSG_SYNC_INDEX 0
#define MSG_ADDR_INDEX 1
#define MSG_CMD_INDEX  2
#define MSG_DATA_INDEX 3
#define MSG_CRC_INDEX  4

#define RELAYS_ALL_ON  0xff
#define RELAYS_ALL_OFF 0x00

#define SERIAL_READ_TIMEOUT_DECISECONDS 5 /* termios VTIME: 0.5 s */

#endif  /* MAIN_BOARD_H */
