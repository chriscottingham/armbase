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

class Blinky : public Task {
private:
	Pin &pin;
	bool state = false;
	uint32_t runDelay = 1000;

public:

	Blinky(Pin& pin, uint32_t runDelay) : pin(pin), runDelay(runDelay) {

		System& system = System::getInstance();
		system.enableClock(pin);
		system.setPinFunctionOutput(pin, System::OutputFunction::PUSH_PULL);

		setState(false);
	}
	virtual ~Blinky(){}

	void start(){
		System::getInstance().queueTask(this, runDelay);
	}

	void run() {
		invertState();
		start();
	}

	Pin& getPin() {
		return pin;
	}

	void setState(bool state) {
		this->state = state;
		System::getInstance().setPinState(pin, state);
	}

	void invertState() {
		setState(!state);
	}

};

#endif /* BLINKY_H_ */
