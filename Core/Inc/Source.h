#ifndef INC_SOURCE_H_
#define INC_SOURCE_H_

#include "Transmitter.h"
#include <string>

class Source
{
    int line;
    int position;
    UART_HandleTypeDef* huart;
public:
    Source(UART_HandleTypeDef* huart);
	virtual ~Source();

	int get_line();
	int get_position();

	char receive_code_char();
	void update_position(uint8_t rx_buffer);
};


#endif /* INC_SOURCE_H_ */
