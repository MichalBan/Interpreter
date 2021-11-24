#include "my_main.h"

// main function called after setup from CUBEMX
void my_main_run(UART_HandleTypeDef* huart)
{
	Program* P = Parser::parse_program();
	Transmitter::start_listening();
	Executor::execute(P);

	for(;;)
	{

	}
}
