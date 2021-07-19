/*
 * Blinky.cpp
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#include "Blinky.h"

Blinky::Blinky(Pin& pin) : pin(pin) {

	System& system = System::getInstance();
	system.enableClock(pin);
	system.setPinFunctionOutput(pin, System::OutputFunction::PUSH_PULL);
}

Blinky::~Blinky() {
	// TODO Auto-generated destructor stub
}

