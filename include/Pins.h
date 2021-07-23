/*
 * pins.h
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#ifndef PINS_H_
#define PINS_H_

#include "Pin.h"
#include "stm32f1xx.h"

class Pins {
private:
	Pin blinkyPin = {12, GPIOB};

	Pins(){}
//	Pins(Pins const&);
//	void operator=(Pins const&);

public:
	Pins(Pins const&) = delete;
	void operator=(Pins const&) = delete;

	static Pins& getInstance() {
		static Pins instance;
		return instance;
	}

	Pin& getBlinkyPin() {
		return blinkyPin;
	}
};

#endif /* PINS_H_ */
