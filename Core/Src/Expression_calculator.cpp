#include <Expression_calculator.h>

Expression_calculator::Expression_calculator()
{

}

Expression_calculator& Expression_calculator::get_instance()
{
	static Expression_calculator instance;
	return instance;
}

Symbol Expression_calculator::evaluate(Expression *exp)
{
	Position_counter::get_instance().line = exp->line;
	Position_counter::get_instance().position = exp->position;

	if (exp->and_exps.size() > 1)
	{
		Symbol var = false; // potrzebna krótsza ścieżka
		for (And_expression *and_exp : exp->and_exps)
		{
			var = var || evaluate(and_exp);
		}
		return var;

	}
	else
	{
		return evaluate(exp->and_exps[0]);
	}
}

Symbol Expression_calculator::evaluate(And_expression *and_exp)
{
	if (and_exp->comp_exps.size() > 1)
	{
		Symbol var = true;
		for (Compare_expression *comp_exp : and_exp->comp_exps)
		{
			var = var && evaluate(comp_exp);
		}
		return var;
	}
	else
	{
		return evaluate(and_exp->comp_exps[0]);
	}
}

Symbol Expression_calculator::evaluate(Compare_expression *comp_exp)
{
	Symbol var = evaluate(comp_exp->left_rel_exp);
	if (comp_exp->right_rel_exp)
	{
		switch (comp_exp->op)
		{
		case COMP_OP_EQUAL:
			var = var == evaluate(comp_exp->right_rel_exp);
			break;
		case COMP_OP_NOT_EQUAL:
			var = !(var == evaluate(comp_exp->right_rel_exp));
			break;
		default:
			Transmitter::report_error("compare operator");
		}
	}

	return var;
}

Symbol Expression_calculator::evaluate(Relation_expression *rel_exp)
{
	Symbol var = evaluate(rel_exp->left_sum_exp);
	if (rel_exp->right_sum_exp)
	{
		switch (rel_exp->op)
		{
		case REL_OP_GREATER:
			return var > evaluate(rel_exp->right_sum_exp);
		case REL_OP_GREATER_EQUAL:
			return var >= evaluate(rel_exp->right_sum_exp);
		case REL_OP_SMALLER:
			return var < evaluate(rel_exp->right_sum_exp);
		case REL_OP_SMALLER_EQUAL:
			return var <= evaluate(rel_exp->right_sum_exp);
		default:
			Transmitter::report_error("relation operator");
		}
	}

	return var;
}

Symbol Expression_calculator::evaluate(Sum_expression *sum_exp)
{
	Symbol var = evaluate(sum_exp->mult_exps[0]);
	for (unsigned int i = 0; i < sum_exp->ops.size(); ++i)
	{
		if (sum_exp->ops[i] == SUM_OP_PLUS)
		{
			var = var + evaluate(sum_exp->mult_exps[i + 1]);
		}
		else
		{
			var = var - evaluate(sum_exp->mult_exps[i + 1]);
		}
	}
	return var;
}

Symbol Expression_calculator::evaluate(Multiply_expression *mult_exp)
{
	Symbol var = evaluate(mult_exp->pow_exps[0]);
	for (unsigned int i = 0; i < mult_exp->ops.size(); ++i)
	{
		if (mult_exp->ops[i] == MULT_OP_MULTIPLY)
		{
			var = var * evaluate(mult_exp->pow_exps[i + 1]);
		}
		else if (mult_exp->ops[i] == MULT_OP_DIVIDE)
		{
			var = var / evaluate(mult_exp->pow_exps[i + 1]);
		}
		else
		{
			var = var % evaluate(mult_exp->pow_exps[i + 1]);
		}
	}
	return var;
}

Symbol Expression_calculator::evaluate(Power_expression *pow_exp)
{
	Symbol var = evaluate(pow_exp->left_un_exp);

	if (pow_exp->right_un_exp)
	{
		Symbol temp = evaluate(pow_exp->right_un_exp);
		var = var ^ temp;
	}

	return var;
}

Symbol Expression_calculator::evaluate(Unary_expression *un_exp)
{
	switch (un_exp->op)
	{
	case UN_OP_NONE:
		return evaluate(un_exp->prior_exp);
	case UN_OP_MINUS:
		return -evaluate(un_exp->prior_exp);
	default:
		return !evaluate(un_exp->prior_exp);
	}
}

Symbol Expression_calculator::evaluate(Priority_expression *prior_exp)
{
	if (std::holds_alternative<Expression*>(prior_exp->exp))
	{
		Expression *exp = std::get<Expression*>(prior_exp->exp);
		return evaluate(exp);
	}
	else
	{
		Primal_expression *exp = std::get<Primal_expression*>(prior_exp->exp);
		return evaluate(exp);
	}
}

Symbol Expression_calculator::evaluate(Primal_expression *primal_exp)
{
	switch (primal_exp->type)
	{
	case PRIMAL_INT:
		return std::get<int>(primal_exp->content);
	case PRIMAL_FLOAT:
		return std::get<float>(primal_exp->content);
	case PRIMAL_STRING:
		return std::get<std::string>(primal_exp->content);
	case PRIMAL_BOOL:
		return std::get<bool>(primal_exp->content);
	case PRIMAL_VARIABLE:
		return evaluate(std::get<Variable*>(primal_exp->content));
	case PRIMAL_FUNCTION_CALL:
		return Function_handler::run_function(
				std::get<Function_call*>(primal_exp->content));
	}
	return 0;
}

Symbol Expression_calculator::evaluate(Variable *var)
{
	Symbol s = Variable_handler::get_instance().get_symbol(*var);

	if (var->index)
	{
		return s[evaluate(var->index)];
	}

	return s;
}
