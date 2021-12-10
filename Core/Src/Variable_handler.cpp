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

void Variable_handler::transmit_variables()
{
    std::string res = "";
	for(auto const& [name, symbol] : Arg)
	{
	    res += name;
	    res += "=";
	    switch(symbol.type)
	    {
		case SYMBOL_INT:
			res += itoa(std::get<int>(symbol.value), nullptr, 10);
			break;
		case SYMBOL_FLOAT:
		{
			char temp[10];
			sprintf(temp, "%f", std::get<float>(symbol.value));
			res += temp;
			break;
		}
		case SYMBOL_BOOL:
			res += std::get<bool>(symbol.value) ? "true" : "false";
			break;
		case SYMBOL_STRING:
			res += std::get<std::string>(symbol.value);
			break;
		case SYMBOL_CONTAINER:
			break;
	    }
	    res += ";";
	}
	res += '\n';
	Transmitter::send_string(res);
}
