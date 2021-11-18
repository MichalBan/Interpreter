#include "Function_handler.h"

token_value Function_handler::run_function(Function_call *fcall)
{
	static Function_handler instance;

	auto search = instance.functions.find(fcall->id);
	if (search != instance.functions.end())
	{
		function_pointer fun = search->second;
		return fun(fcall->arguments);
	}
	else
	{
		Transmitter::report_error(std::string("function " + fcall->id + " not found"),
				fcall->line, fcall->position);
		return 0;
	}
}
