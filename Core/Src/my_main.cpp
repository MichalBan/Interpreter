#include "my_main.h"

// main function called after setup from CUBEMX
void my_main_run(UART_HandleTypeDef* huart)
{
	Source Com(huart);
	Transmitter Trans(huart);
	Lexer Lex(&Com);
	Parser Par(&Lex, &Trans);

	Program* P = Par.parse_program();
	delete P;

	for(;;)
	{

	}
}
