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
	std::string create_symbol_message(std::string name, Symbol symbol);
	void transmit_variables();
	void create_symbol_message_recursively(Symbol symbol,
			const std::string &name, std::string &res);
	void create_symbol_message_simply(const std::string &name,
			const Symbol &symbol, std::string &res);
};

#endif /* INC_VARIABLE_HANDLER_H_ */
