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

class System {
private:
	System();

public:
	static System& getInstance() {
		static System system;
		return system;
	}
	System(System const&) = delete;
	void operator=(System const&) = delete;

	void enableClock(Pin& pin);
};



#endif /* SYSTEM_H_ */
