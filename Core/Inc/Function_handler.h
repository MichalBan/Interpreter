#ifndef INC_FUNCTION_HANDLER_H_
#define INC_FUNCTION_HANDLER_H_

#include "Expression.h"
#include "Transmitter.h"

typedef token_value (*function_pointer)(std::vector<Expression*>);

#define ADD_FUNCTION(x) functions.insert({#x, &x});

class Function_handler
{
	Function_handler();
	Function_handler(Function_handler const&);
	void operator=(Function_handler const&);

	std::map<std::string, function_pointer> functions;

public:
	static token_value run_function(Function_call *fcall);
};

#endif /* INC_FUNCTION_HANDLER_H_ */
