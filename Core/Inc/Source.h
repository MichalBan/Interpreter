#ifndef INC_SOURCE_H_
#define INC_SOURCE_H_

#include "Transmitter.h"
#include <string>

class Source
{
    int line;
    int position;

	void update_position(uint8_t rx_buffer);
public:
    Source();
	~Source();

	int get_line();
	int get_position();
	char receive_code_char();
};


#endif /* INC_SOURCE_H_ */
