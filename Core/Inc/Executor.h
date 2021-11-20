#ifndef INC_EXECUTOR_H_
#define INC_EXECUTOR_H_

#include "Function_handler.h"
#include "Variable_handler.h"
#include "Parser.h"

class Executor
{
	void execute(If_statement s);
	void execute(While_statement s);
	void execute(Method_call mcall);
	void execute(Function_call fcall);
	void execute(Assignment assign);
	void execute(Statement stat);
public:
	void execute(Program p);
};

#endif /* INC_EXECUTOR_H_ */
