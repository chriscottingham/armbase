/*
 * System.h
 *
 *  Created on: Jul 18, 2021
 *      Author: becomingguru
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#define GET_GPIO(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))

#include <list>
#include <functional>
#include <vector>
#include <queue>

#include "Pin.h"
#include "Task.h"

#include "stm32f1xx.h"

class System {
private:
	struct TaskEntry {
		uint32_t maturationTime;
		Task *task;
	};

	struct TaskEntryComparator {
		bool operator()( TaskEntry*& lhs, TaskEntry*& rhs )  {
			return lhs->maturationTime > rhs->maturationTime;
		}
	};

	uint32_t clock = 0;

	std::priority_queue<TaskEntry*, std::vector<TaskEntry*>, TaskEntryComparator> taskEntries;

	System() {
		SysTick_Config(10000);
	}

public:

	enum OutputFunction {
		PUSH_PULL, OPEN_DRAIN
	};

	enum InputFunction {
		ANALOG, INPUT_FLOATING, INPUT_PULL_DOWN, INPUT_PULL_UP
	};

	static System& getInstance() {
		static System system;
		return system;
	}
	System(System const&) = delete;
	void operator=(System const&) = delete;

	void enableClock(Pin &pin) {

		uint8_t ioEnableMask = 0;

		if (pin.port == GPIOA) {
			ioEnableMask = 4;
		} else if (pin.port == GPIOB) {
			ioEnableMask = 8;
		}

		RCC->APB2ENR |= ioEnableMask;
	}

	void setPinFunctionAlternate(Pin &pin, OutputFunction outputFunction) {

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

	void initPin(Pin &pin, GPIO_InitTypeDef &GPIO_InitStructure) {
		GPIO_InitStructure.Pin = 1 << pin.pinNumber;
		GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(pin.port, &GPIO_InitStructure);
	}

	void setPinState(Pin &pin, bool state) {
		HAL_GPIO_WritePin(pin.port, 1 << pin.pinNumber, (GPIO_PinState) state);
	}

	void queueTask(Task *task, uint16_t delay) {
		taskEntries.push(new TaskEntry { clock + delay, task });
	}

	void setPinFunctionOutput(Pin &pin, OutputFunction outputFunction) {

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

	void setPinFunctionInput(Pin &pin, InputFunction inputFunction) {

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

	void tick() {
		if (!taskEntries.empty()) {
			++clock;
			while (!taskEntries.empty()) {
				TaskEntry *taskEntry = taskEntries.top();
				if (clock >= taskEntry->maturationTime) {
					taskEntries.pop();
					taskEntry->task->run();
					delete taskEntry;
				} else {
					break;
				}
			}
		}
	}
};

#endif /* SYSTEM_H_ */
