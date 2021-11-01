#include <Transmitter.h>

Transmitter::Transmitter(UART_HandleTypeDef* huart)
{
	this->huart = huart;
}

Transmitter::~Transmitter()
= default;

void Transmitter::report_error(std::string message, int line, int position)
{
	std::string full_message = message + "\nin line: " + itoa(line, nullptr, 10) + " in position: " + itoa(position, nullptr, 10) + "\n";
#ifndef TESTS
	__disable_irq();
	while (1)
	{
		HAL_UART_Transmit(huart, (uint8_t*)full_message.c_str(), full_message.length(), 100);
		HAL_Delay(500);
	}
#else
	std::cout << full_message;
#endif
}
