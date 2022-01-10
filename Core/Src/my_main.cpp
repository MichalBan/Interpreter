#include "my_main.h"

// main function called after setup from CUBEMX
void my_main_run()
{
	Dialog_handler::get_instance().metadata_dialog();
	Program *P = Parser::parse_program();
	Transmitter::start_listening();
	Executor::get_instance().execute(P);

	for (;;)
	{

	}
}
