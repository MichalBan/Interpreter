#include <Transmitter.h>

extern UART_HandleTypeDef huart1;

uint8_t Transmitter::get_rx_buffer()
{
	return rx_buffer;
}

void Transmitter::report_error(std::string message, int line, int position)
{
	std::string full_message = message + "\nin line: " + itoa(line, nullptr, 10)
			+ " in position: " + itoa(position, nullptr, 10) + "\n";
#ifndef TESTS
	while (1)
	{
		HAL_UART_Transmit(&huart1, (uint8_t*) full_message.c_str(),
				full_message.length(), 100);
		HAL_Delay(500);
	}
#else
	std::cout << full_message;
#endif
}

#ifndef TESTS
void Transmitter::start_listening()
{
	HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	switch (Transmitter::get_rx_buffer())
	{
	case 'e':
		break;
	default:
		break;
	}
}
#endif
