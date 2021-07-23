/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"

#include "timer.h"

#include "Main.h"
#include "System.h"
#include "Pins.h"
#include "Blinky.h"

namespace {
	// ----- Timing definitions -------------------------------------------------

	// Keep the LED on for 2/3 of a second.
//	constexpr timer::ticks_t BLINK_ON_TICKS = timer::FREQUENCY_HZ * 3 / 4;
//	constexpr timer::ticks_t BLINK_OFF_TICKS = timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

//#include "cortexm/exception-handlers.h"
#include "Pin.h"
#include "cmsis_device.h"

int main(int argc, char *argv[]) {

	trace_puts("Hello Arm World!");
	trace_printf("System clock: %u Hz\n", SystemCoreClock);

	Blinky blinky(Pins::getInstance().getBlinkyPin());

	System::getInstance().queueTask(blinky.getRunner(), 1000);

	// Infinite loop
	while (1) {
		// Count seconds on the trace device.
//		trace_printf("Second %u\n", seconds);
	}
	// Infinite loop, never return.
}

extern "C" void SysTick_Handler(void) {
	System::getInstance().tick();
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
