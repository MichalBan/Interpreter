#include <Variable_handler.h>

Variable_handler& Variable_handler::get_instance()
{
	static Variable_handler instance;
	return instance;
}

Symbol& Variable_handler::get_arg(std::string name)
{
	auto search = Arg.find(name);
	if(search == Arg.end())
	{
		Transmitter::report_error(std::string("Arg " + name + " not found"));
	}
	return search->second;
}

Symbol& Variable_handler::get_par(std::string name)
{
	auto search = Par.find(name);
	if(search == Par.end())
	{
		Transmitter::report_error(std::string("Par " + name + " not found"));
	}
	return search->second;
}

Symbol& Variable_handler::get_local(std::string name)
{
	return local[name];
}

Symbol& Variable_handler::get_symbol(Variable var)
{
	switch(var.type)
	{
	case VARIABLE_ARG:
		return get_arg(var.id);
	case VARIABLE_PAR:
		return get_par(var.id);
	case VARIABLE_LOCAL:
		break;
	}
	return get_local(var.id);
}
