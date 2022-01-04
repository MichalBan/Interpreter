#include "Parser.h"

void Parser::parse_variable_or_function_call(Primal_expression *exp)
{
	std::string id(std::get<std::string>(token_buffer.value));
	get_next_token();
	if (token_buffer.type == TOKEN_LEFT_BRACKET)
	{
		exp->type = PRIMAL_FUNCTION_CALL;
		exp->content = parse_function_call(id);
	}
	else
	{
		exp->type = PRIMAL_VARIABLE;
		exp->content = parse_variable(id);
	}
}

Primal_expression* Parser::parse_primal_expression()
{
	auto exp = new Primal_expression();
	switch(token_buffer.type)
	{
	case TOKEN_TRUE:
		exp->type = PRIMAL_BOOL;
		exp->content = true;
		get_next_token();
		break;
	case TOKEN_FALSE:
		exp->type = PRIMAL_BOOL;
		exp->content = false;
		get_next_token();
	case TOKEN_INT:
		exp->type = PRIMAL_INT;
		exp->content = std::get<int>(token_buffer.value);
		get_next_token();
		break;
	case TOKEN_FLOAT:
		exp->type = PRIMAL_FLOAT;
		exp->content = std::get<float>(token_buffer.value);
		get_next_token();
		break;
	case TOKEN_STRING:
		exp->type = PRIMAL_STRING;
		exp->content = std::string(std::get<std::string>(token_buffer.value));
		get_next_token();
		break;
	case TOKEN_IDENTIFIER:
		parse_variable_or_function_call(exp);
		break;
	default:
		Transmitter::report_error("expression");
		break;
	}
	return exp;
}

Expression* Parser::parse_nested_expression()
{
	auto exp = parse_expression();
	assert_token(TOKEN_RIGHT_BRACKET, "closing bracket");
	get_next_token();
	return exp;
}

Priority_expression* Parser::parse_priority_expression()
{
	auto exp = new Priority_expression();
	if(token_buffer.type == TOKEN_LEFT_BRACKET)
	{
		get_next_token();
		exp->exp = parse_nested_expression();
	}
	else
	{
		exp->exp = parse_primal_expression();
	}
	return exp;
}

bool Parser::match_unary_operator(Unary_expression* exp)
{
	switch(token_buffer.type)
	{
	case TOKEN_MINUS:
		exp->op = UN_OP_MINUS;
		break;
	case TOKEN_EXCLAMATION:
		exp->op = UN_OP_EXCLAMATION;
		break;
	default:
		return false;
	}
	return true;
}

Unary_expression* Parser::parse_unary_expression()
{
	auto exp = new Unary_expression();
	if(match_unary_operator(exp))
	{
		get_next_token();
	}
	exp->prior_exp = parse_priority_expression();
	return exp;
}

Power_expression* Parser::parse_power_expression()
{
	auto exp = new Power_expression();
	exp->left_un_exp = parse_unary_expression();
	if(token_buffer.type == TOKEN_POWER)
	{
		get_next_token();
		exp->right_un_exp = parse_unary_expression();
	}
	else
	{
		exp->right_un_exp = nullptr;
	}
	return exp;
}

bool Parser::match_multiply_operator(Multiply_expression* exp)
{
	switch(token_buffer.type)
	{
	case TOKEN_MULTIPLY:
		exp->ops.push_back(MULT_OP_MULTIPLY);
		break;
	case TOKEN_DIVIDE:
		exp->ops.push_back(MULT_OP_DIVIDE);
		break;
	case TOKEN_MODULO:
		exp->ops.push_back(MULT_OP_MODULO);
		break;
	default:
		return false;
	}
	return true;
}

Multiply_expression* Parser::parse_multiply_expression()
{
	auto exp = new Multiply_expression();
	exp->pow_exps.push_back(parse_power_expression());
	while(match_multiply_operator(exp))
	{
		get_next_token();
		exp->pow_exps.push_back(parse_power_expression());
	}
	return exp;
}

bool Parser::match_sum_operator(Sum_expression* exp)
{
	switch(token_buffer.type)
	{
	case TOKEN_PLUS:
		exp->ops.push_back(SUM_OP_PLUS);
		break;
	case TOKEN_MINUS:
		exp->ops.push_back(SUM_OP_MINUS);
		break;
	default:
		return false;
	}
	return true;
}

Sum_expression* Parser::parse_sum_expression()
{
	auto exp = new Sum_expression();
	exp->mult_exps.push_back(parse_multiply_expression());
	while(match_sum_operator(exp))
	{
		get_next_token();
		exp->mult_exps.push_back(parse_multiply_expression());
	}
	return exp;
}

bool Parser::match_relation_operator(Relation_expression* exp)
{
	switch (token_buffer.type)
	{
	case TOKEN_SMALLER_THAN:
		exp->op = REL_OP_SMALLER;
		break;
	case TOKEN_SMALLER_OR_EQUAL:
		exp->op = REL_OP_SMALLER_EQUAL;
		break;
	case TOKEN_GREATER_THAN:
		exp->op = REL_OP_GREATER;
		break;
	case TOKEN_GREATER_OR_EQUAL:
		exp->op = REL_OP_SMALLER_EQUAL;
		break;
	default:
		exp->right_sum_exp = nullptr;
		return false;
	}
	return true;
}

Relation_expression* Parser::parse_relation_expression()
{
	auto exp = new Relation_expression();
	exp->left_sum_exp = parse_sum_expression();
	if(match_relation_operator(exp))
	{
		get_next_token();
		exp->right_sum_exp = parse_sum_expression();
	}
	return exp;
}

bool Parser::match_compare_operator(Compare_expression *exp)
{
	switch (token_buffer.type)
	{
	case TOKEN_EQUALS:
		exp->op = COMP_OP_EQUAL;
		break;
	case TOKEN_NOT_EQUAL:
		exp->op = COMP_OP_NOT_EQUAL;
		break;
	default:
		exp->right_rel_exp = nullptr;
		return false;
	}
	return true;
}

Compare_expression* Parser::parse_compare_expression()
{
	auto exp = new Compare_expression();
	exp->left_rel_exp = parse_relation_expression();
	if(match_compare_operator(exp))
	{
		get_next_token();
		exp->right_rel_exp = parse_relation_expression();
	}
	return exp;
}

And_expression* Parser::parse_and_expression()
{
	auto exp = new And_expression();
	exp->comp_exps.push_back(parse_compare_expression());
	while(token_buffer.type == TOKEN_AND)
	{
		get_next_token();
		exp->comp_exps.push_back(parse_compare_expression());
	}
	return exp;
}

Expression* Parser::parse_expression()
{
	auto exp = new Expression();
	exp->line = Position_counter::get_instance().get_line();
	exp->position = Position_counter::get_instance().get_position();
	exp->and_exps.push_back(parse_and_expression());
	while(token_buffer.type == TOKEN_OR)
	{
		get_next_token();
		exp->and_exps.push_back(parse_and_expression());
	}
	return exp;
}
