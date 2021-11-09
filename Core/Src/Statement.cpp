#include <Statement.h>

Body::~Body()
{
	for (Statement *s : statements)
	{
		delete s;
	}
}

Statement::~Statement()
{
	switch (type)
	{
	case STATEMENT_ASSIGNMENT:
		delete std::get<Assignment*>(content);
		break;
	case STATEMENT_FUNCTION_CALL:
		delete std::get<Function_call*>(content);
		break;
	case STATEMENT_METHOD_CALL:
		delete std::get<Method_call*>(content);
		break;
	case STATEMENT_WHILE:
		delete std::get<While_statement*>(content);
		break;
	case STATEMENT_IF:
		delete std::get<If_statement*>(content);
		break;
	}
}

While_statement::~While_statement()
{
	delete condition;
	delete while_body;
}

If_statement::~If_statement()
{
	for (Expression *e : conditions)
	{
		delete e;
	}

	for (Body *b : if_bodies)
	{
		delete b;
	}
}

Function_call::~Function_call()
{
	for (Expression *e : arguments)
	{
		delete e;
	}
}

Method_call::~Method_call()
{
	delete call;
}

Assignment::~Assignment()
{
	delete value;
	delete var;
}

Variable::~Variable()
{
	delete index;
}
