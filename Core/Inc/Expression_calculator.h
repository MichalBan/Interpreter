#ifndef SRC_EXPRESSIONCALCULATOR_H_
#define SRC_EXPRESSIONCALCULATOR_H_

#include "Expression.h"
#include <math.h>

class Expression_calculator
{
	static bool get_int(int* var, Primal_expression* primal_exp);
	static bool get_int(int* var, Priority_expression* prior_exp);
	static bool get_int(int* var, Unary_expression* un_exp);
	static bool get_int(int* var, Power_expression* pow_exp);
	static bool get_int(int* var, Multiply_expression* mult_exp);
	static bool get_int(int* var, Sum_expression* sum_exp);
public:
	static bool get_int(int* var, Expression* exp);
	static bool get_float(float* var, Expression* exp);
	static bool get_bool(bool* var, Expression* exp);
	static bool get_string(std::string* var, Expression* exp);

	Expression_calculator();
	virtual ~Expression_calculator();
};

#endif /* SRC_EXPRESSIONCALCULATOR_H_ */
