#include <Expression_calculator.h>

int Expression_calculator::line = 0;
int Expression_calculator::position = 0;

int Expression_calculator::get_int(Expression *exp)
{
	line = exp->line;
	position = exp->position;
	if (exp->and_exps.size() != 1)
	{
		Transmitter::report_error("integer", line, position);
	}
	And_expression *and_exp = exp->and_exps[0];
	if (and_exp->comp_exps.size() != 1)
	{
		Transmitter::report_error("integer", line, position);
	}
	Compare_expression *comp_exp = and_exp->comp_exps[0];
	if (comp_exp->op != COMP_OP_NONE)
	{
		Transmitter::report_error("integer", line, position);
	}
	Relation_expression *rel_exp = comp_exp->left_rel_exp;
	if (rel_exp->op != REL_OP_NONE)
	{
		Transmitter::report_error("integer", line, position);
	}
	Sum_expression *sum_exp = rel_exp->left_sum_exp;

	return get_int(sum_exp);
}

int Expression_calculator::get_int(Sum_expression *sum_exp)
{
	int var = 0;
	for (Multiply_expression *mult_exp : sum_exp->mult_exps)
	{
		var += get_int(mult_exp);
	}
	return var;
}

int Expression_calculator::get_int(Multiply_expression *mult_exp)
{
	int var = 1;
	for (Power_expression *pow_exp : mult_exp->pow_exps)
	{
		var *= get_int(pow_exp);
	}
	return var;
}

int Expression_calculator::get_int(Power_expression *pow_exp)
{
	int var = get_int(pow_exp->left_un_exp);

	if (pow_exp->right_un_exp)
	{
		int temp = get_int(pow_exp->right_un_exp);
		var = pow(var, temp);
	}

	return var;
}

int Expression_calculator::get_int(Unary_expression *un_exp)
{
	switch (un_exp->op)
	{
	case UN_OP_NONE:
		return get_int(un_exp->prior_exp);
		break;
	case UN_OP_MINUS:
		return -get_int(un_exp->prior_exp);
		break;
	default:
		Transmitter::report_error("integer", line, position);
		break;
	}
	return 0;
}

int Expression_calculator::get_int(Priority_expression *prior_exp)
{
	if(std::holds_alternative<Expression*>(prior_exp->exp))
	{
		Expression* exp = std::get<Expression*>(prior_exp->exp);
		return get_int(exp);
	}
	else
	{
		Primal_expression* exp = std::get<Primal_expression*>(prior_exp->exp);
		return get_int(exp);
	}
}

int Expression_calculator::get_int(Primal_expression *primal_exp)
{
	switch(primal_exp->type)
	{
	case PRIMAL_INT:
		return std::get<int>(primal_exp->content);
	case PRIMAL_FLOAT:
		return (int)(std::get<float>(primal_exp->content));
	case PRIMAL_VARIABLE:
		return 0; //todo
	case PRIMAL_FUNCTION_CALL:
		return get_function_int(primal_exp);
	default:
		Transmitter::report_error("integer", line, position);
		return 0;
	}
}

int Expression_calculator::get_function_int(Primal_expression* exp)
{
	Function_call* function_call = std::get<Function_call*>(exp->content);
	auto val = Function_handler::run_function(function_call);
	return std::get<int>(val);
}

float Expression_calculator::get_float(Expression *exp)
{
	return 0;
}

bool Expression_calculator::get_bool(Expression *exp)
{
	return false;
}

std::string Expression_calculator::get_string(Expression *exp)
{
	return "";
}
