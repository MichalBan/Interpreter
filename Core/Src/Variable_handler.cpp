#include <Variable_handler.h>

Variable_handler& Variable_handler::get_instance()
{
	static Variable_handler instance;
	return instance;
}

Symbol& Variable_handler::get_arg(std::string name)
{
	auto search = Arg.find(name);
	if (search == Arg.end())
	{
		Transmitter::report_error(std::string("Arg " + name + " not found"));
	}
	return search->second;
}

Symbol& Variable_handler::get_par(std::string name)
{
	auto search = Par.find(name);
	if (search == Par.end())
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
	switch (var.type)
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

void Variable_handler::create_symbol_message_recursively(Symbol symbol,
		const std::string &name, std::string &res)
{
	int i = 0;
	for (Symbol s : std::get<std::vector<Symbol> >(symbol.value))
	{
		std::string sname = name + std::to_string(i);
		res += create_symbol_message(sname, s);
		++i;
	}
}

void Variable_handler::create_symbol_message_simply(const std::string &name,
		const Symbol &symbol, std::string &res)
{
	res += name;
	res += "=";
	res += symbol.to_string();
	res += ";";
}

std::string Variable_handler::create_symbol_message(std::string name, Symbol symbol)
{
	std::string res = "";
	if(symbol.type == SYMBOL_CONTAINER)
	{
		create_symbol_message_recursively(symbol, name, res);
	}
	else if (symbol.type != SYMBOL_STRING)
	{
		create_symbol_message_simply(name, symbol, res);
	}
	return res;
}

void Variable_handler::transmit_variables()
{
	std::string res = "";
	for (auto const& [name, symbol] : Arg)
	{
		res += create_symbol_message(name, symbol);
	}
	for (auto const& [name, symbol] : Par)
	{
		res += create_symbol_message(name, symbol);
	}
	for (auto const& [name, symbol] : local)
	{
		res += create_symbol_message(name, symbol);
	}
	res += '\n';
	Transmitter::send_string(res);
}
