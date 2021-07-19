/*
 * System.cpp
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#include "System.h"
#include "Pin.h"

System::System() {
}

void System::enableClock(Pin &pin) {

	uint8_t ioEnableMask = 0;

	if (pin.port == GPIOA){
		ioEnableMask = 4;
	} else if (pin.port == GPIOB){
		ioEnableMask = 8;
	}

	RCC->APB2ENR |= ioEnableMask;
}

