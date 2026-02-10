/*
 * AHT20.h
 *
 *  Created on: Jan 31, 2026
 *      Author: LHH1021
 */

#ifndef INC_AHT20_H_
#define INC_AHT20_H_
#include "main.h"

#define AHT20_ADDRESS (0x38<<1) // AHT20 I2C address shifted for 8-bit addressing

extern float temperature, humidity;

int8_t AHT20_Init(void);  // Initialize AHT20
int8_t AHT20_Read(void);  // Read AHT20 data


#endif /* INC_AHT20_H_ */
