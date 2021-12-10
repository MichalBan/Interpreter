#include <Executor.h>

Executor::Executor()
{

}

Executor& Executor::get_instance()
{
	static Executor instance;
	return instance;
}

void Executor::execute_loop(Body *loop)
{
	Symbol &loops = Variable_handler::get_instance().get_local("loops");
	Symbol &max_loops = Variable_handler::get_instance().get_local("max_loops");
	while ((max_loops == 0 || loops < max_loops).get_bool())
	{
		execute(loop);
		Variable_handler::get_instance().transmit_variables();
		loops = loops + 1;
	}
}

void Executor::execute(Program *p)
{
	this->p = p;
	execute(p->setup);
	execute_loop(p->loop);
	Transmitter::send_string("fin\n");
	execute(p->finish);
}

void Executor::execute(Body *bod)
{
	for (Statement *s : bod->statements)
	{
		execute(s);
	}
}

void Executor::execute(Statement *stat)
{
	switch (stat->type)
	{
	case STATEMENT_ASSIGNMENT:
		execute(std::get<Assignment*>(stat->content));
		break;
	case STATEMENT_FUNCTION_CALL:
		execute(std::get<Function_call*>(stat->content));
		break;
	case STATEMENT_METHOD_CALL:
		execute(std::get<Method_call*>(stat->content));
		break;
	case STATEMENT_WHILE:
		execute(std::get<While_statement*>(stat->content));
		break;
	case STATEMENT_IF:
		execute(std::get<If_statement*>(stat->content));
		break;
	}
}

void Executor::execute(If_statement *ifst)
{
	for (unsigned int i = 0; i < ifst->conditions.size(); ++i)
	{
		Symbol condition_symbol = EVALUATE(ifst->conditions[i]);
		if (condition_symbol.get_bool())
		{
			execute(ifst->if_bodies[i]);
			return;
		}
	}

	if (ifst->conditions.size() < ifst->if_bodies.size())
	{
		execute(ifst->if_bodies.back());
	}
}

void Executor::execute(While_statement *whist)
{
	bool condition = true;
	while (condition)
	{
		execute(whist->while_body);
		Symbol condition_symbol = EVALUATE(whist->condition);
		condition = condition_symbol.get_bool();
	}
}

void Executor::execute(Method_call *mcall)
{
	Method_handler::run_method(mcall);
}

void Executor::execute(Function_call *fcall)
{
	Function_handler::run_function(fcall);
}

void Executor::execute(Assignment *assign)
{
	Symbol &variable = Variable_handler::get_instance().get_symbol(
			*assign->var);
	Symbol value = EVALUATE(assign->value);

	if (assign->var->index)
	{
		variable.type = SYMBOL_CONTAINER;
		int idx = check_index(assign->var->index);
		variable.resize(idx + 1);
		variable[idx] = value;
	}
	else
	{
		variable = value;
	}
}

int Executor::check_index(Expression *exp)
{
	Symbol idx_symbol = EVALUATE(exp);
	int i = std::get<int>(idx_symbol.value);
	if (i < 0)
	{
		Transmitter::report_error("index can not be negative");
	}
	return i;
}

void Executor::abort()
{
	if (p)
	{
		execute(p->finish);
	}
	Transmitter::send_string("fin\n");
	Transmitter::report_error("aborted by user");
}
