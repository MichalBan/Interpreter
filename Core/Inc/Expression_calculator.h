#ifndef SRC_EXPRESSIONCALCULATOR_H_
#define SRC_EXPRESSIONCALCULATOR_H_

#include "Expression.h"
#include "Transmitter.h"
#include "Function_handler.h"
#include <math.h>

class Expression_calculator
{
	static int line;
	static int position;

	static int get_int(Primal_expression* primal_exp);
	static int get_int(Priority_expression* prior_exp);
	static int get_int(Unary_expression* un_exp);
	static int get_int(Power_expression* pow_exp);
	static int get_int(Multiply_expression* mult_exp);
	static int get_int(Sum_expression* sum_exp);
	static int get_function_int(Primal_expression* exp);
public:
	static int get_int(Expression* exp);
	static float get_float(Expression* exp);
	static bool get_bool(Expression* exp);
	static std::string get_string(Expression* exp);
};

#endif /* SRC_EXPRESSIONCALCULATOR_H_ */
