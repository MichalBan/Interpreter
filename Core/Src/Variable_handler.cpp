#include <Variable_handler.h>

Variable_handler& Variable_handler::get_instance()
{
	static Variable_handler instance;
	return instance;
}

Symbol& Variable_handler::get_arg(std::string name)
{
	return Arg[name];
}

Symbol& Variable_handler::get_par(std::string name)
{
	return Par[name];
}

Symbol& Variable_handler::get_local(std::string name)
{
	return local[name];
}

void Variable_handler::add_local(std::string name, Symbol)
{
	local.insert({name, {}});
}
