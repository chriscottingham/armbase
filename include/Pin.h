/*
 * Pin.h
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#ifndef PIN_H_
#define PIN_H_

#include <stdint.h>
#include "stm32f1xx.h"

typedef struct Pin {
	uint8_t pinNumber;
	GPIO_TypeDef* port;
} Pin;




#endif /* PIN_H_ */
