#include "Function_handler.h"

Symbol Function_handler::run_function(Function_call *fcall)
{
	static Function_handler instance;

	Position_counter::get_instance().line = fcall->line;
	Position_counter::get_instance().position = fcall->position;

	auto search = instance.functions.find(fcall->id);
	if (search != instance.functions.end())
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
