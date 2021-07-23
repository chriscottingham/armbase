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
	bool state = false;

public:

	class BlinkRunner : public Task {
	private:
		Blinky* blinky;

	public:
		BlinkRunner(Blinky* blinky) : blinky(blinky) {}
		void run() {
			blinky->invertState();
			System::getInstance().queueTask(this, 1000);
		}
		~BlinkRunner() {}
	};

	Blinky(Pin& pin) : pin(pin) {

		System& system = System::getInstance();
		system.enableClock(pin);
		system.setPinFunctionOutput(pin, System::OutputFunction::PUSH_PULL);

		setState(false);
	}
	virtual ~Blinky(){}

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

	BlinkRunner* getRunner() {
		static BlinkRunner runner(this);
		return &runner;
	}

};

#endif /* BLINKY_H_ */
