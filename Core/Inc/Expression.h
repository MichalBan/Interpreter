#ifndef EXPRESSION_CLASSES_H_
#define EXPRESSION_CLASSES_H_

#include "identifier_classes.h"
#include "Token.h"

typedef enum
{
	PRIMAL_BOOL,
	PRIMAL_INT,
	PRIMAL_FLOAT,
	PRIMAL_STRING,
	PRIMAL_VARIABLE,
	PRIMAL_FUNCTION_CALL
}primal_type;

class Primal_expression
{
public:
	~Primal_expression();
	primal_type type;
	std::variant<bool, int, float, std::string, Variable*, Function_call*> content;
};

class Expression;

class Priority_expression
{
public:
	~Priority_expression();
	std::variant<Primal_expression*, Expression*> exp;
};

typedef enum
{
	UN_OP_NONE,
	UN_OP_MINUS,
	UN_OP_EXCLAMATION,
}un_operator;

class Unary_expression
{
public:
	~Unary_expression();
	Priority_expression* prior_exp;
	un_operator op;
};

class Power_expression
{
public:
	~Power_expression();
	Unary_expression* left_un_exp;
	Unary_expression* right_un_exp;
};

typedef enum
{
	MULT_OP_NONE,
	MULT_OP_MULTIPLY,
	MULT_OP_DIVIDE,
	MULT_OP_MODULO
}mult_operator;

class Multiply_expression
{
public:
	~Multiply_expression();
	std::vector<Power_expression*> pow_exps;
	std::vector<mult_operator> ops;
};

typedef enum
{
	SUM_OP_PLUS,
	SUM_OP_MINUS
}sum_operator;

class Sum_expression
{
public:
	~Sum_expression();
	std::vector<Multiply_expression*> mult_exps;
	std::vector<sum_operator> ops;
};

typedef enum
{
	REL_OP_NONE,
	REL_OP_SMALLER,
	REL_OP_SMALLER_EQUAL,
	REL_OP_GREATER,
	REL_OP_GREATER_EQUAL
}rel_operator;

class Relation_expression
{
public:
	~Relation_expression();
	Sum_expression* left_sum_exp;
	Sum_expression* right_sum_exp;
	rel_operator op;
};

typedef enum
{
	COMP_OP_NONE,
	COMP_OP_EQUAL,
	COMP_OP_NOT_EQUAL
}comp_operator;

class Compare_expression
{
public:
	~Compare_expression();
	Relation_expression* left_rel_exp;
	Relation_expression* right_rel_exp;
	comp_operator op;
};

class And_expression
{
public:
	~And_expression();
	std::vector<Compare_expression*> comp_exps;
};

class Expression
{
public:
    int line;
    int position;
	std::vector<And_expression*> and_exps;
	~Expression();
};

#endif /* EXPRESSION_CLASSES_H_ */
