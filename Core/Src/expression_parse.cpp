#include "Parser.h"

void Parser::parse_variable_or_function_call(Primal_expression &exp)
{
	std::string id(std::get<std::string>(token_buffer.get_value()));
	get_next_token();
	if (token_buffer.get_type() == TOKEN_LEFT_BRACKET)
	{
		exp.type = PRIMAL_FUNCTION_CALL;
		exp.content = new Function_call(parse_function_call(id));
	}
	else
	{
		exp.type = PRIMAL_VARIABLE;
		exp.content = new Variable(parse_variable(id));
	}
}

Primal_expression Parser::parse_primal_expression()
{
	Primal_expression exp;
	switch(token_buffer.get_type())
	{
	case TOKEN_TRUE:
		exp.type = PRIMAL_BOOL;
		exp.content = true;
		get_next_token();
		break;
	case TOKEN_FALSE:
		exp.type = PRIMAL_BOOL;
		exp.content = false;
		get_next_token();
	case TOKEN_INT:
		exp.type = PRIMAL_INT;
		exp.content = std::get<int>(token_buffer.get_value());
		get_next_token();
		break;
	case TOKEN_FLOAT:
		exp.type = PRIMAL_FLOAT;
		exp.content = std::get<float>(token_buffer.get_value());
		get_next_token();
		break;
	case TOKEN_STRING:
		exp.type = PRIMAL_STRING;
		exp.content = std::string(std::get<std::string>(token_buffer.get_value()));
		get_next_token();
		break;
	case TOKEN_IDENTIFIER:
		parse_variable_or_function_call(exp);
		break;
	default:
		report_error("expression");
		break;
	}
	return exp;
}

void Parser::parse_nested_expression(Priority_expression &exp)
{
	get_next_token();
	exp.exp = new Expression(parse_expression());
	assert_token(TOKEN_RIGHT_BRACKET, "closing bracket");
	get_next_token();
}

Priority_expression Parser::parse_priority_expression()
{
	Priority_expression exp;
	if(token_buffer.get_type() == TOKEN_LEFT_BRACKET)
	{
		parse_nested_expression(exp);
	}
	else
	{
		exp.exp = new Primal_expression(parse_primal_expression());
	}
	return exp;
}

bool Parser::match_unary_operator(Unary_expression& exp)
{
	switch(token_buffer.get_type())
	{
	case TOKEN_MINUS:
		exp.op = UN_OP_MINUS;
		break;
	case TOKEN_EXCLAMATION:
		exp.op = UN_OP_EXCLAMATION;
		break;
	default:
		return false;
	}
	return true;
}

Unary_expression Parser::parse_unary_expression()
{
	Unary_expression exp{};
	if(match_unary_operator(exp))
	{
		get_next_token();
	}
	exp.prior_exp = new Priority_expression(parse_priority_expression());
	return exp;
}

Power_expression Parser::parse_power_expression()
{
	Power_expression exp{};
	exp.left_un_exp = new Unary_expression(parse_unary_expression());
	if(token_buffer.get_type() == TOKEN_POWER)
	{
		get_next_token();
		exp.right_un_exp = new Unary_expression(parse_unary_expression());
	}
	else
	{
		exp.right_un_exp = nullptr;
	}
	return exp;
}

bool Parser::match_multiply_operator(Multiply_expression& exp)
{
	switch(token_buffer.get_type())
	{
	case TOKEN_MULTIPLY:
		exp.ops.push_back(MULT_OP_MULTIPLY);
		break;
	case TOKEN_DIVIDE:
		exp.ops.push_back(MULT_OP_DIVIDE);
		break;
	case TOKEN_MODULO:
		exp.ops.push_back(MULT_OP_MODULO);
		break;
	default:
		return false;
	}
	return true;
}

Multiply_expression Parser::parse_multiply_expression()
{
	Multiply_expression exp;
	exp.pow_exps.push_back(new Power_expression(parse_power_expression()));
	while(match_multiply_operator(exp))
	{
		get_next_token();
		exp.pow_exps.push_back(new Power_expression(parse_power_expression()));
	}
	return exp;
}

bool Parser::match_sum_operator(Sum_expression& exp)
{
	switch(token_buffer.get_type())
	{
	case TOKEN_PLUS:
		exp.ops.push_back(SUM_OP_PLUS);
		break;
	case TOKEN_MINUS:
		exp.ops.push_back(SUM_OP_MINUS);
		break;
	default:
		return false;
	}
	return true;
}

Sum_expression Parser::parse_sum_expression()
{
	Sum_expression exp;
	exp.mult_exps.push_back(new Multiply_expression(parse_multiply_expression()));
	while(match_sum_operator(exp))
	{
		get_next_token();
		exp.mult_exps.push_back(new Multiply_expression(parse_multiply_expression()));
	}
	return exp;
}

bool Parser::match_relation_operator(Relation_expression& exp)
{
	switch (token_buffer.get_type())
	{
	case TOKEN_SMALLER_THAN:
		exp.op = REL_OP_SMALLER;
		break;
	case TOKEN_SMALLER_OR_EQUAL:
		exp.op = REL_OP_SMALLER_EQUAL;
		break;
	case TOKEN_GREATER_THAN:
		exp.op = REL_OP_GREATER;
		break;
	case TOKEN_GREATER_OR_EQUAL:
		exp.op = REL_OP_SMALLER_EQUAL;
		break;
	default:
		exp.right_sum_exp = nullptr;
		return false;
	}
	return true;
}

Relation_expression Parser::parse_relation_expression()
{
	Relation_expression exp{};
	exp.left_sum_exp = new Sum_expression(parse_sum_expression());
	if(match_relation_operator(exp))
	{
		get_next_token();
		exp.right_sum_exp = new Sum_expression(parse_sum_expression());
	}
	return exp;
}

bool Parser::match_compare_operator(Compare_expression &exp)
{
	switch (token_buffer.get_type())
	{
	case TOKEN_EQUALS:
		exp.op = COMP_OP_EQUAL;
		break;
	case TOKEN_NOT_EQUAL:
		exp.op = COMP_OP_NOT_EQUAL;
		break;
	default:
		exp.right_rel_exp = nullptr;
		return false;
	}
	return true;
}

Compare_expression Parser::parse_compare_expression()
{
	Compare_expression exp{};
	exp.left_rel_exp = new Relation_expression(parse_relation_expression());
	if(match_compare_operator(exp))
	{
		get_next_token();
		exp.right_rel_exp = new Relation_expression(parse_relation_expression());
	}
	return exp;
}

And_expression Parser::parse_and_expression()
{
	And_expression exp;
	exp.comp_exps.push_back(new Compare_expression(parse_compare_expression()));
	while(token_buffer.get_type() == TOKEN_AND)
	{
		get_next_token();
		exp.comp_exps.push_back(new Compare_expression(parse_compare_expression()));
	}
	return exp;
}

Expression Parser::parse_expression()
{
	Expression exp;
	exp.and_exps.push_back(new And_expression(parse_and_expression()));
	while(token_buffer.get_type() == TOKEN_OR)
	{
		get_next_token();
		exp.and_exps.push_back(new And_expression(parse_and_expression()));
	}
	return exp;
}
