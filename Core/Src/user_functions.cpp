#include "Expression_calculator.h"
#include "Variable_handler.h"

namespace
{

Symbol run_single_experiment_iteration(arglist arguments = { })
{
	Symbol x = 5;

	if (arguments.size() > 0)
	{
		x = EVALUATE(arguments[0]);
	}

	ARG(x) = 3;
	x = ARG(x);
	ARG(messages) = "hello";
	x = ARG(messages);
	ARG(messages) = 2.54f;
	x = ARG(messages);

	ARG(messages) = { "hello", "world" };
	Symbol m = ARG(messages);
	Symbol h = m[0];
	Symbol w = m[1];
	return x;
}

}

Function_handler::Function_handler()
{
	ADD_FUNCTION(run_single_experiment_iteration);
}

Variable_handler::Variable_handler()
{
	ADD_ARG(x);
	ADD_ARG(messages);
}
