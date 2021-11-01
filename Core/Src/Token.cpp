#include <utility>

#include "Token.h"

Token::~Token()
= default;

token_value Token::get_value()
{
	return value;
}

void Token::set_value(token_value value)
{
	this->value = std::move(value);
}

token_type Token::get_type()
{
	return type;
}

void Token::set_type(token_type type)
{
	this->type = type;
}

int Token::get_line()
{
	return line;
}

void Token::set_line(int line)
{
	this->line = line;
}

int Token::get_position()
{
	return position;
}
void Token::set_position(int position)
{
	this->position = position;
}
