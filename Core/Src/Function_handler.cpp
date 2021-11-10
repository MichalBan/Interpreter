#include <Function_handler.h>

namespace
{
	void run_single_experiment_iteration(arglist arguments = { })
	{
		int x = 2;
		++x;
	}

}

Function_handler::Function_handler()
{
	FUNCTION(run_single_experiment_iteration);
}
