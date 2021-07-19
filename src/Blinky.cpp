/*
 * Blinky.cpp
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#include "Blinky.h"

Blinky::Blinky(Pin& pin) : pin(pin) {

	System::getInstance().enableClock(pin);
}

Blinky::~Blinky() {
	// TODO Auto-generated destructor stub
}

