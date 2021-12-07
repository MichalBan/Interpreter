#include "my_main.h"

// main function called after setup from CUBEMX
void my_main_run(UART_HandleTypeDef *huart)
{
	if (false)
	{
		Transmitter::send_result();
		Transmitter::send_result();
		Transmitter::send_result();
		Transmitter::send_result(true);
	}

	Program *P = Parser::parse_program();
	Transmitter::start_listening();
	Executor::get_instance().execute(P);

	for (;;)
	{

	}
}
