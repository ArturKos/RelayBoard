/**
 * @file crc.h
 * @brief CRC8 checksum for the relay board wire protocol.
 */

#ifndef CRC_BOARD_H
#define CRC_BOARD_H

#include <stdint.h>

/**
 * @brief Computes CRC8 over bytes 1..3 of a 5-byte protocol frame.
 *
 * The sync byte at index 0 and the CRC slot at index 4 are ignored;
 * only the device-address, command and data bytes participate.
 * Uses a 256-entry lookup table with seed 0x00.
 *
 * @param c Pointer to a frame buffer of at least 4 bytes.
 * @return CRC8 of bytes c[1], c[2], c[3].
 */
uint8_t CountCRC(uint8_t *c);

#endif  /* CRC_BOARD_H */
