#include "Expression_calculator.h"
#include "Variable_handler.h"

namespace
{
using namespace std;

token_value run_single_experiment_iteration(arglist arguments = { })
{
	int x = 5;

	if (arguments.size() > 0)
	{
		x = Expression_calculator::get_int(arguments[0]);
	}

	ARG(x) = 3;
	x = get<int>(ARG(x));

	ARG(messages) = vector<string>{ "hello", "world" };
	string h = get<vector<string>>(ARG(messages))[0];
	string w = get<vector<string>>(ARG(messages))[1];
	return x;
}

}

Function_handler::Function_handler()
{
	ADD_FUNCTION(run_single_experiment_iteration);
}

Variable_handler::Variable_handler()
{
	ADD_ARG(x, INT);
	ADD_ARG(messages, STRING_CONTAINER);
}
