/*
 * System.h
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#define GET_GPIO(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))

#include "Pin.h"
#include "stm32f1xx.h"

class System {
private:
	System();

public:
	enum OutputFunction {
		PUSH_PULL,
		OPEN_DRAIN
	};
	enum InputFunction {
		ANALOG,
		INPUT_FLOATING,
		INPUT_PULL_DOWN,
		INPUT_PULL_UP
	};

	static System& getInstance() {
		static System system;
		return system;
	}
	System(System const&) = delete;
	void operator=(System const&) = delete;

	void enableClock(Pin& pin);

	void setPinFunctionAlternate(Pin& pin, OutputFunction outputFunction);
	void setPinFunctionOutput(Pin& pin, OutputFunction outputFunction);
	void setPinFunctionInput(Pin& pin, InputFunction inputFunction);

	void setPinState(Pin& pin, bool state);
};



#endif /* SYSTEM_H_ */
