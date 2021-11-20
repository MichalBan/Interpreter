#include <Position_counter.h>

Position_counter::Position_counter()
{
	line = 1;
	position = 0;
}

Position_counter& Position_counter::get_instance()
{
	static Position_counter instance;
	return instance;
}

void Position_counter::update_position(uint8_t rx_buffer)
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
