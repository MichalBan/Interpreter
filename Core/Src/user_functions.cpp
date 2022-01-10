#include "Expression_calculator.h"
#include "Variable_handler.h"
#include <sys/time.h>

namespace
{

Symbol run_single_experiment_iteration(arglist arguments = { })
{
	static Symbol sum_e = 0;
	static Symbol e = {0, 0};

	// uchyb
	e[0] = PAR(yzad) - ARG(y)[0];
	sum_e = sum_e + e[0];

	//regulator
	ARG(u)[0] = PAR(P)*e[0] + PAR(I)*sum_e + PAR(D)*(e[0] - e[1]);

	//obiekt
	ARG(y)[0] = ARG(u)[0] - ARG(u)[1]*0.5 + ARG(y)[0]*0.5 + ARG(y)[1]*0.25;


	e[1] = e[0];
	ARG(y)[1] = ARG(y)[0];
	ARG(u)[1] = ARG(u)[0];

	return 0;
}

Symbol get_time_ms(arglist arguments = { })
{
    return (int)HAL_GetTick();
}

}

Function_handler::Function_handler()
{
	ADD_FUNCTION(run_single_experiment_iteration);
	ADD_FUNCTION(get_time_ms);
}

Variable_handler::Variable_handler()
{
	ADD_ARG(u);
	ADD_ARG(y);

	ADD_PAR(yzad);
	ADD_PAR(P);
	ADD_PAR(I);
	ADD_PAR(D);
}
