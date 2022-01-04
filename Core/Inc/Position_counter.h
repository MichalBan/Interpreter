#ifndef INC_POSITION_COUNTER_H_
#define INC_POSITION_COUNTER_H_

#include "Singleton_starter_pack.h"
#include "stm32f7xx_hal.h"

class Position_counter
{
	SINGLETON(Position_counter)
    int line;
    int position;
    uint8_t last_char;
    int last_line_length;

public:
	static Position_counter& get_instance();

	void update_position(uint8_t rx_buffer);
	int get_line();
	void set_line(int line);
	int get_position();
	void set_position(int position);
};

#endif /* INC_POSITION_COUNTER_H_ */
