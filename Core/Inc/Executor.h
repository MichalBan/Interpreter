#ifndef INC_EXECUTOR_H_
#define INC_EXECUTOR_H_

#include "Expression_calculator.h"
#include "Method_handler.h"
#include "Function_handler.h"
#include "Variable_handler.h"
#include "Parser.h"

class Executor
{
	Program* p;
	SINGLETON(Executor)

	void execute(If_statement* ifst);
	void execute(While_statement* whist);
	void execute(Method_call* mcall);
	void execute(Function_call* fcall);
	void execute(Assignment* assign);
	void execute(Statement* stat);
	void execute(Body* bod);
	void execute_loop(Body *loop);

	int check_index(Expression* exp);
public:
	static Executor& get_instance();

	void execute(Program* p);
	void abort();
};

#endif /* INC_EXECUTOR_H_ */
