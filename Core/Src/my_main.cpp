#include "my_main.h"

// main function called after setup from CUBEMX
void my_main_run(UART_HandleTypeDef* huart)
{
	Parser Par;

	Program* P = Par.parse_program();
	delete P;

	//Executor Exec;
	auto fc = new Function_call();
	fc->id = std::string("run_single_experiment_iteration");
	fc->arguments = {};

	Function_handler::run_function(fc);

	delete fc;

	for(;;)
	{

	}
}
