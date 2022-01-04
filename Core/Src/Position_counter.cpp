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
	last_char = rx_buffer;
	if (rx_buffer == '\n')
	{
		++line;
		last_line_length = position;
		position = 0;
	}
	else
	{
		++position;
	}
}

int Position_counter::get_line()
{
	if (last_char == '\n')
	{
		return line - 1;
	}
	else
	{
		return line;
	}
}

int Position_counter::get_position()
{
	if (last_char == '\n')
	{
		return last_line_length;
	}
	else
	{
		return position;
	}
}

void Position_counter::set_line(int line)
{
	this->line = line;
}

void Position_counter::set_position(int position)
{
	this->position = position;
}
