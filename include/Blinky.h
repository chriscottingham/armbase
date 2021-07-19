/*
 * Blinky.h
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#ifndef BLINKY_H_
#define BLINKY_H_

#include "System.h"
#include "Pin.h"

class Blinky {
private:
	Pin &pin;

public:
	Blinky(Pin &pin);

	virtual ~Blinky();

	Pin& getPin() {
		return pin;
	}

	void setState(bool state) {
		System::getInstance().setPinState(pin, state);
	}
};

#endif /* BLINKY_H_ */
