#ifndef INC_VARIABLE_HANDLER_H_
#define INC_VARIABLE_HANDLER_H_

#include "Expression.h"
#include "Transmitter.h"
#include "Symbol.h"

#define ADD_ARG(x) Arg.insert({#x, {}});
#define ARG(x) Variable_handler::get_instance().get_arg(#x)
#define ADD_PAR(x) Par.insert({#x, {}});
#define PAR(x) Variable_handler::get_instance().get_par(#x)

class Variable_handler
{
	std::map<std::string, Symbol> local;
	std::map<std::string, Symbol> Par;
	std::map<std::string, Symbol> Arg;

	SINGLETON(Variable_handler)
public:
	static Variable_handler& get_instance();

	Symbol& get_arg(std::string name);
	Symbol& get_par(std::string name);
	Symbol& get_local(std::string name);
	Symbol& get_symbol(Variable var);
	void transmit_variables();
};

#endif /* INC_VARIABLE_HANDLER_H_ */
