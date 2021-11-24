#ifndef INC_METHOD_HANDLER_H_
#define INC_METHOD_HANDLER_H_

#include "Expression_calculator.h"
#include "Variable_handler.h"
#include "Transmitter.h"
#include "Symbol.h"

typedef void (*method_pointer)(Symbol&, arglist);

#define ADD_METHOD(x) methods.insert({#x, &x});

class Method_handler
{
	SINGLETON(Method_handler)

	std::map<std::string, method_pointer> methods;
public:
	static void run_method(Method_call *mcall);
};

#endif /* INC_METHOD_HANDLER_H_ */
