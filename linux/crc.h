/**
 * @file crc.h
 * @brief Header file for CRC calculation functions.
 *
 * This file contains the declaration of the function used to calculate
 * the CRC (Cyclic Redundancy Check) for a given data array.
 */

 /**
    * @brief Calculates the CRC for the given data array.
    *
    * This function takes a pointer to an array of bytes and calculates
    * the CRC value for the data.
    *
    * @param c Pointer to the data array for which the CRC is to be calculated.
    * @return The calculated CRC value.
    */
#ifndef CRC_BOARD_H
#define CRC_BOARD_H
#include <stdint.h>

extern uint8_t CountCRC(uint8_t* c);

#endif  // CRC_BOARD_H