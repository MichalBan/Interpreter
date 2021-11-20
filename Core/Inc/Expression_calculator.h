#ifndef SRC_EXPRESSIONCALCULATOR_H_
#define SRC_EXPRESSIONCALCULATOR_H_

#include "Expression.h"
#include "Transmitter.h"
#include "Function_handler.h"
#include "Variable_handler.h"
#include <math.h>

#define EVALUATE(x) Expression_calculator::get_instance().evaluate(x);

class Expression_calculator
{
	Expression_calculator() = default;
	Expression_calculator(Expression_calculator const&);
	void operator=(Expression_calculator const&);

	Symbol evaluate(Variable* var);
	Symbol evaluate(Primal_expression* primal_exp);
	Symbol evaluate(Priority_expression* prior_exp);
	Symbol evaluate(Unary_expression* un_exp);
	Symbol evaluate(Power_expression* pow_exp);
	Symbol evaluate(Multiply_expression* mult_exp);
	Symbol evaluate(Sum_expression* sum_exp);
	Symbol evaluate(Relation_expression* rel_exp);
	Symbol evaluate(Compare_expression* comp_exp);
	Symbol evaluate(And_expression* and_exp);
public:
	static Expression_calculator& get_instance();

	Symbol evaluate(Expression* exp);
};

#endif /* SRC_EXPRESSIONCALCULATOR_H_ */
