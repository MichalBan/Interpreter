#ifndef INC_POSITION_COUNTER_H_
#define INC_POSITION_COUNTER_H_

#include "Singleton_starter_pack.h"
#include "stm32f7xx_hal.h"

class Position_counter
{
	SINGLETON(Position_counter)

public:
    int line;
    int position;
	static Position_counter& get_instance();

	void update_position(uint8_t rx_buffer);
	int get_line();
	int get_position();
};

#endif /* INC_POSITION_COUNTER_H_ */
