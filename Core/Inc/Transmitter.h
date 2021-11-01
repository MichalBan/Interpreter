#ifndef INC_TRANSMITTER_H_
#define INC_TRANSMITTER_H_

#define TESTS

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
    UART_HandleTypeDef* huart;
public:
	Transmitter(UART_HandleTypeDef* huart);
	virtual ~Transmitter();
    void report_error(std::string message, int line, int position);
};

#endif /* INC_TRANSMITTER_H_ */