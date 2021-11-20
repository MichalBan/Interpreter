#ifndef INC_TRANSMITTER_H_
#define INC_TRANSMITTER_H_

#include <Position_counter.h>
#include <string>

class Transmitter
{
public:
	static uint8_t get_rx_buffer();
	static char receive_code_char();
	static void report_error(std::string message);
	static void start_listening();
};

#endif /* INC_TRANSMITTER_H_ */
