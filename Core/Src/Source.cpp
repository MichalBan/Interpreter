#include <Source.h>

#ifdef TESTS
static std::ifstream indata{};
#endif

Source::Source(UART_HandleTypeDef* huart)
{
	line = 1;
	position = 0;
	this->huart = huart;
#ifdef TESTS
    indata.open("code.txt");
#endif
}

Source::~Source()
{
#ifdef TESTS
    indata.close();
#endif
}

int Source::get_line()
{
	return line;
}

int Source::get_position()
{
	return position;
}

// update line and position in line depending on received char
void Source::update_position(uint8_t rx_buffer)
{
	if (rx_buffer == '\n')
	{
		++line;
		position = 0;
	}
	else
	{
		++position;
	}
}

// receive char with UART in blocking mode
char Source::receive_code_char()
{
    static uint8_t rx_buffer;
#ifndef TESTS
    static uint8_t tx_buf;
    tx_buf = 'c';
	HAL_UART_Transmit(huart, &tx_buf, 1, 100);
	HAL_UART_Receive(huart, &rx_buffer, 1, -1);
#else
	rx_buffer = (uint8_t)indata.get();
#endif
	update_position(rx_buffer);

	return rx_buffer;
}
