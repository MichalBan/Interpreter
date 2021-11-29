#include "Transmitter.h"
#include "Executor.h"

extern UART_HandleTypeDef huart1;
static uint8_t rx_buffer;

uint8_t Transmitter::get_rx_buffer()
{
	return rx_buffer;
}

void Transmitter::report_error(std::string message)
{
	std::string line = itoa(Position_counter::get_instance().line, nullptr, 10);
	std::string position = itoa(Position_counter::get_instance().position, nullptr, 10);

	std::string full_message = "$" + message + "\nin line: " + line
			+ " in position: " + position + "\n";

	while (1)
	{
		HAL_UART_Transmit(&huart1, (uint8_t*) full_message.c_str(),
				full_message.length(), 100);
		HAL_Delay(500);
	}
}

void Transmitter::start_listening()
{
	HAL_UART_Receive_IT(&huart1, &rx_buffer, 1);
}

char Transmitter::receive_code_char()
{
    static uint8_t tx_buffer = 'c';
	HAL_UART_Transmit(&huart1, &tx_buffer, 1, 100);
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

void Transmitter::send_result(bool fin)
{
	static std::string res;
    res = "x=12.2;y=56;P=2;I=1;D=0.05;\n";
    if(fin)
    {
    	res = "fin\n";
    }
	HAL_UART_Transmit(&huart1, (uint8_t*)res.c_str(), res.length(), 100);
}
