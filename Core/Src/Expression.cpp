#include <Expression.h>

Primal_expression::~Primal_expression()
{
	if(std::holds_alternative<Variable*>(content))
	{
		delete std::get<Variable*>(content);
	}
	else if(std::holds_alternative<Function_call*>(content))
	{
		delete std::get<Function_call*>(content);
	}
}

Priority_expression::~Priority_expression()
{
	if(std::holds_alternative<Expression*>(exp))
	{
		delete std::get<Expression*>(exp);
	}
	else
	{
		delete std::get<Primal_expression*>(exp);
	}
}

Unary_expression::~Unary_expression()
{
	delete prior_exp;
}

Power_expression::~Power_expression()
{
	delete left_un_exp;
	delete right_un_exp;
}

Multiply_expression::~Multiply_expression()
{
	for(Power_expression* exp : pow_exps)
	{
		delete exp;
	}
}

Sum_expression::~Sum_expression()
{
	for(Multiply_expression* exp : mult_exps)
	{
		delete exp;
	}
}

Relation_expression::~Relation_expression()
{
	delete left_sum_exp;
	delete right_sum_exp;
}

Compare_expression::~Compare_expression()
{
	delete left_rel_exp;
	delete right_rel_exp;
}

And_expression::~And_expression()
{
	for(Compare_expression* exp : comp_exps)
	{
		delete exp;
	}
}

Expression::~Expression()
{
	for(And_expression* exp : and_exps)
	{
		delete exp;
	}
}
