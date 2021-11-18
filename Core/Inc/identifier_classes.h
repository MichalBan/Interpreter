#ifndef INC_IDENTIFIER_CLASSES_H_
#define INC_IDENTIFIER_CLASSES_H_

#include <string>
#include <vector>

class Expression;

typedef std::vector<Expression*> arglist;

typedef enum
{
	ASSIGNMENT_LOCAL,
	ASSIGNMENT_ARG,
	ASSIGNMENT_PAR,
}variable_type;

class Variable
{
public:
	~Variable();
	variable_type type;
	std::string id;
	Expression* index;
};

class Function_call
{
public:
	~Function_call();
	int line;
	int position;
	std::string id;
	arglist arguments;
};

class Method_call
{
public:
	~Method_call();
	int line;
	int position;
	std::string vector_id;
	Function_call* call;
};


#endif /* INC_IDENTIFIER_CLASSES_H_ */
