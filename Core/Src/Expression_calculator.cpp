#include <Expression_calculator.h>

Expression_calculator::Expression_calculator()
{
	// TODO Auto-generated constructor stub

}

Expression_calculator::~Expression_calculator()
{
	// TODO Auto-generated destructor stub
}

bool Expression_calculator::get_int(int *var, Expression *exp)
{
	if (exp->and_exps.size() != 1)
	{
		return false;
	}
	And_expression *and_exp = exp->and_exps[0];
	if (and_exp->comp_exps.size() != 1)
	{
		return false;
	}
	Compare_expression *comp_exp = and_exp->comp_exps[0];
	if (comp_exp->op != COMP_OP_NONE)
	{
		return false;
	}
	Relation_expression *rel_exp = comp_exp->left_rel_exp;
	if (rel_exp->op != REL_OP_NONE)
	{
		return false;
	}
	Sum_expression *sum_exp = rel_exp->left_sum_exp;
	if (!get_int(var, sum_exp))
	{
		return false;
	}
	return true;
}

bool Expression_calculator::get_int(int *var, Sum_expression *sum_exp)
{
	*var = 0;
	int temp = 0;
	for (Multiply_expression *mult_exp : sum_exp->mult_exps)
	{
		if (get_int(&temp, mult_exp))
		{
			*var += temp;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Expression_calculator::get_int(int *var,
		Multiply_expression *mult_exp)
{
	*var = 1;
	int temp = 0;
	for (Power_expression *pow_exp : mult_exp->pow_exps)
	{
		if (get_int(&temp, pow_exp))
		{
			*var *= temp;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool Expression_calculator::get_int(int *var, Power_expression *pow_exp)
{
	if (!get_int(var, pow_exp->left_un_exp))
	{
		return false;
	}
	if (pow_exp->right_un_exp)
	{
		int temp = 0;
		if (!get_int(&temp, pow_exp->right_un_exp))
		{
			return false;
		}
		*var = pow(*var, temp);
	}

	return true;
}

bool Expression_calculator::get_int(int *var, Unary_expression *un_exp)
{
	switch (un_exp->op)
	{
	case UN_OP_NONE:
		break;
	case UN_OP_MINUS:
		break;
	default:
		return false;
		break;
	}
	return true;
}

bool Expression_calculator::get_int(int *var,
		Priority_expression *prior_exp)
{
	return true;
}

bool Expression_calculator::get_int(int *var,
		Primal_expression *primal_exp)
{
	return true;
}

bool Expression_calculator::get_float(float *var, Expression *exp)
{
	return true;
}

bool Expression_calculator::get_bool(bool *var, Expression *exp)
{
	return true;
}

bool Expression_calculator::get_string(std::string *var, Expression *exp)
{
	return true;
}
