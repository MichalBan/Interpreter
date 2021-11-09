#ifndef INC_STATEMENT_H_
#define INC_STATEMENT_H_

#include "Expression.h"

class Statement;

class Body
{
public:
	~Body();
	std::vector<Statement*> statements;
};

class If_statement
{
public:
	~If_statement();
	std::vector<Expression*> conditions;
	std::vector<Body*> if_bodies;
};

class While_statement
{
public:
	~While_statement();
	Expression* condition;
	Body* while_body;
};

class Assignment
{
public:
	~Assignment();
	Variable* var;
	Expression* value;
};

typedef enum
{
	STATEMENT_ASSIGNMENT,
	STATEMENT_FUNCTION_CALL,
	STATEMENT_METHOD_CALL,
	STATEMENT_WHILE,
	STATEMENT_IF
}statement_type;

typedef std::variant<Assignment*, Function_call*, Method_call*, While_statement*, If_statement*> statement_content;

class Statement
{
public:
	~Statement();
	statement_type type;
	statement_content content;
};

#endif /* INC_STATEMENT_H_ */
