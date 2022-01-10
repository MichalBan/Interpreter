#include "Transmitter.h"
#include "Executor.h"

extern UART_HandleTypeDef huart1;

void Transmitter::report_error(std::string message)
{
	std::string line = std::to_string(Position_counter::get_instance().get_line());
	std::string position = std::to_string(Position_counter::get_instance().get_position());

	std::string full_message = "$" + message + " in line: " + line
			+ " in position: " + position + "\n";

	while (1)
	{
		HAL_UART_Transmit(&huart1, (uint8_t*) full_message.c_str(),
				full_message.length(), 100);
		HAL_Delay(5000);
	}
}

void Transmitter::send_string(std::string message)
{
	static std::string res;
    res = message;
	HAL_UART_Transmit(&huart1, (uint8_t*)res.c_str(), res.length(), 1000);
}

static uint8_t rx_buffer;

void Transmitter::start_listening()
{
	HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);
}

char Transmitter::get_choice()
{
	HAL_UART_Receive(&huart1, &rx_buffer, 1, -1);
	return rx_buffer;
}

char Transmitter::receive_code_char()
{
    static uint8_t tx_buffer = 'c';
	HAL_UART_Transmit(&huart1, &tx_buffer, 1, 1000);
	HAL_UART_Receive(&huart1, &rx_buffer, 1, -1);

	Position_counter::get_instance().update_position(rx_buffer);

	return rx_buffer;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	switch (rx_buffer)
	{
	case 'e':
		Executor::get_instance().abort();
		break;
	default:
		break;
	}
}
