#ifndef INC_FUNCTION_HANDLER_H_
#define INC_FUNCTION_HANDLER_H_

#include "Expression.h"
#include "Transmitter.h"
#include "Symbol.h"

typedef Symbol (*function_pointer)(arglist);

#define ADD_FUNCTION(x) functions.insert({#x, &x});

class Function_handler
{
	SINGLETON(Function_handler)

	std::map<std::string, function_pointer> functions;
public:
	static Symbol run_function(Function_call *fcall);
};

#endif /* INC_FUNCTION_HANDLER_H_ */
