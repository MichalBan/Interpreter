#include <Method_handler.h>

namespace
{
	// todo dober miejsce


	void assert_arguments(int expected, arglist arguments)
	{
		if(arguments.size() != (unsigned int)expected)
		{
			Transmitter::report_error(std::string("expected " + std::to_string(expected) + " arguments, found " + std::to_string(arguments.size()) + "\n"));
		}
	}

void resize(Symbol& var, arglist arguments)
{
	assert_arguments(1, arguments);
	Symbol size_symbol = EVALUATE(arguments[0]);
	size_symbol.assert_type(SYMBOL_INT);
	int size = std::get<int>(size_symbol.value);
	var.resize(size);
}

}

Method_handler::Method_handler()
{
	ADD_METHOD(resize);
}

void Method_handler::run_method(Method_call *mcall)
{
	static Method_handler instance;

	Position_counter::get_instance().line = mcall->call->line;
	Position_counter::get_instance().position = mcall->call->position;

	auto search = instance.methods.find(mcall->call->id);
	if (search == instance.methods.end())
	{
		Transmitter::report_error(std::string("method " + mcall->call->id + " not found"));
	}
	method_pointer method = search->second;

	Symbol& var = Variable_handler::get_instance().get_symbol(*mcall->vector);

	method(var, mcall->call->arguments);
}
