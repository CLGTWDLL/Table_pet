/*
 * key.h
 *
 *  Created on: Jan 30, 2026
 *      Author: LHH1021
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_

#include "main.h"
#include <stdbool.h>
extern bool Key1Pressed, Key2Pressed, Key3Pressed, Key4Pressed, Key5Pressed;

void key_debounce(void);

#endif /* INC_KEY_H_ */
