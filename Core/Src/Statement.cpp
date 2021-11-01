#include <Statement.h>

Body::~Body()
{
	for(Statement* s : statements)
	{
		delete s;
	}
}

If_statement::~If_statement()
{
	for(Expression* e : conditions)
	{
		delete e;
	}

	for(Body* b : if_bodies)
	{
		delete b;
	}
}

Function_call::~Function_call()
{
	for(Expression* e : arguments)
	{
		delete e;
	}
}

Assignment::~Assignment()
{
	delete value;
}

Variable::~Variable()
{
	delete index;
}
