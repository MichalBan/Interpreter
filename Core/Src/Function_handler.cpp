#include "Function_handler.h"

Function_handler& Function_handler::get_instance()
{
	static Function_handler instance;
	return instance;
}

void Function_handler::transmit_function_names()
{
	std::string message = "";
	for (auto const& [name, pointer] : functions)
	{
		message += name + "; ";
	}
	message += "\n";
	Transmitter::send_string(message);
}

Symbol Function_handler::run_function(Function_call *fcall)
{
	Position_counter::get_instance().set_line(fcall->line);
	Position_counter::get_instance().set_position(fcall->position);

	auto search = functions.find(fcall->id);
	if (search != functions.end())
	{
		function_pointer fun = search->second;
		return fun(fcall->arguments);
	}
	else
	{
		Transmitter::report_error(std::string("function " + fcall->id + " not found"));
		return {};
	}
}
