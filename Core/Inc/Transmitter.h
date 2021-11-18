#ifndef INC_TRANSMITTER_H_
#define INC_TRANSMITTER_H_

//#define TESTS

#ifndef TESTS
#include "stm32f7xx_hal.h"
#else
#include <stdio.h>
#include <iostream>
#include <fstream>
typedef int UART_HandleTypeDef;
#endif

#include <string>

class Transmitter
{
	static uint8_t rx_buffer;
public:
	static uint8_t get_rx_buffer();
	static void report_error(std::string message, int line, int position);
	static void start_listening();
};

#endif /* INC_TRANSMITTER_H_ */
