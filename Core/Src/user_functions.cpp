#include "Expression_calculator.h"
#include "Variable_handler.h"

namespace
{

Symbol run_single_experiment_iteration(arglist arguments = { })
{
	static Symbol past_y = 0.0;
	static Symbol past_u = 0.0;

	static Symbol past_e = 0.0;
	static Symbol sum_e = 0.0;
	static Symbol e = 0.0;

	// uchyb
	e = PAR(yzad) - ARG(y);
	sum_e = sum_e + e;

	//regulator
	ARG(u) = PAR(P)*e + PAR(I)*sum_e + PAR(D)*(e - past_e);

	//obiekt
	ARG(y) = ARG(u) - past_u*0.5 + ARG(y)*0.5 + past_y*0.25;

	past_e = e;
	past_y = ARG(y);
	past_u = ARG(u);

	return 0;
}

}

Function_handler::Function_handler()
{
	ADD_FUNCTION(run_single_experiment_iteration);
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
