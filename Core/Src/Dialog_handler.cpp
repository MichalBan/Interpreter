#include "Dialog_handler.h"

Dialog_handler::Dialog_handler()
{

}

Dialog_handler& Dialog_handler::get_instance()
{
	static Dialog_handler instance;
	return instance;
}

void Dialog_handler::metadata_dialog()
{
	Transmitter::send_string("r");
	char choice = Transmitter::get_choice();
	while (choice == 'm')
	{
		Function_handler::get_instance().transmit_function_names();
		choice = Transmitter::get_choice();
	}
}
