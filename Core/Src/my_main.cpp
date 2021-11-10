#include "my_main.h"

// main function called after setup from CUBEMX
void my_main_run(UART_HandleTypeDef* huart)
{
	Source Com(huart);
	Transmitter Trans(huart);
	Lexer Lex(&Com);
	Parser Par(&Lex, &Trans);

//	Program* P = Par.parse_program();
//	delete P;

	Executor Exec(&Trans);
	Statement st;
	auto fc = new Function_call();
	fc->id = std::string("run_single_experiment_iteration");
	fc->arguments = {};
	st.content = fc;

	Exec.run_function(&st);

	for(;;)
	{

	}
}
