#include <Variable_handler.h>

Variable_handler* Variable_handler::get_instance()
{
	static Variable_handler instance;
	return &instance;
}

symbol_value& Variable_handler::get_arg(std::string name)
{
	return Arg[name].value;
}

symbol_value& Variable_handler::get_par(std::string name)
{
	return Par[name].value;
}

symbol_value& Variable_handler::get_local(std::string name)
{
	return local[name].value;
}
