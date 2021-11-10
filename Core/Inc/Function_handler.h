#ifndef INC_FUNCTION_HANDLER_H_
#define INC_FUNCTION_HANDLER_H_

#include "Expression.h"

typedef void (*function_pointer)(std::vector<Expression*>);

#define FUNCTION(x) functions.insert({#x, &x});

class Function_handler
{
public:
	std::map<std::string, function_pointer> functions;

	Function_handler();
};

#endif /* INC_FUNCTION_HANDLER_H_ */
