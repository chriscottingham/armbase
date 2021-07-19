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

	if (pin.port == GPIOA) {
		ioEnableMask = 4;
	}
	else if (pin.port == GPIOB) {
		ioEnableMask = 8;
	}

	RCC->APB2ENR |= ioEnableMask;
}

void initPin(Pin &pin, GPIO_InitTypeDef &GPIO_InitStructure) {
	GPIO_InitStructure.Pin = 1 << pin.pinNumber;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(pin.port, &GPIO_InitStructure);
}

void System::setPinState(Pin &pin, bool state) {
	HAL_GPIO_WritePin(pin.port, 1 << pin.pinNumber, (GPIO_PinState) state);
}

void System::setPinFunctionAlternate(Pin &pin, OutputFunction outputFunction) {

	GPIO_InitTypeDef GPIO_InitStructure;

	switch (outputFunction) {
		case PUSH_PULL:
			GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
			break;
		case OPEN_DRAIN:
			GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
			break;
	}
	initPin(pin, GPIO_InitStructure);
}

void System::setPinFunctionOutput(Pin &pin, OutputFunction outputFunction) {

	GPIO_InitTypeDef GPIO_InitStructure;

	switch (outputFunction) {
		case PUSH_PULL:
			GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
			break;
		case OPEN_DRAIN:
			GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
			break;
	}
	initPin(pin, GPIO_InitStructure);
}

void System::setPinFunctionInput(Pin &pin, InputFunction inputFunction) {

	GPIO_InitTypeDef GPIO_InitStructure;

	switch (inputFunction) {
		case ANALOG:
			GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
			break;
		case INPUT_FLOATING:
			GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
			break;
		case INPUT_PULL_DOWN:
			GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
			GPIO_InitStructure.Pull = GPIO_PULLDOWN;
			break;
		case INPUT_PULL_UP:
			GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
			GPIO_InitStructure.Pull = GPIO_PULLUP;
			break;
	}
	initPin(pin, GPIO_InitStructure);
}

