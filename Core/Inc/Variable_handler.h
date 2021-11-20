#ifndef INC_VARIABLE_HANDLER_H_
#define INC_VARIABLE_HANDLER_H_

#include "Expression.h"
#include "Transmitter.h"
#include "Symbol.h"

#define ADD_ARG(x) Arg.insert({#x, {}});
#define ARG(x) Variable_handler::get_instance().get_arg(#x)


class Variable_handler
{
	std::map<std::string, Symbol> local;
	std::map<std::string, Symbol> Par;
	std::map<std::string, Symbol> Arg;

	Variable_handler();
	Variable_handler(Variable_handler const&);
	void operator=(Variable_handler const&);
public:
	static Variable_handler& get_instance();

	Symbol& get_arg(std::string name);
	Symbol& get_par(std::string name);
	Symbol& get_local(std::string name);
	void add_local(std::string name, Symbol);
};

#endif /* INC_VARIABLE_HANDLER_H_ */
