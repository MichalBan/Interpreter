#ifndef INC_VARIABLE_HANDLER_H_
#define INC_VARIABLE_HANDLER_H_

#include "Expression.h"
#include "Transmitter.h"
#include <typeinfo>

typedef std::variant<int, float, bool, std::string, std::vector<std::string>,
		std::vector<int>, std::vector<float>, std::vector<bool>> symbol_value;


#define ADD_ARG(name, type) Arg.insert({#name, {SYMBOL_##type, 0}});
#define ARG(x) Variable_handler::get_instance()->get_arg(#x)

typedef enum
{
	SYMBOL_INT,
	SYMBOL_FLOAT,
	SYMBOL_BOOL,
	SYMBOL_STRING,
	SYMBOL_INT_CONTAINER,
	SYMBOL_FLOAT_CONTAINER,
	SYMBOL_BOOL_CONTAINER,
	SYMBOL_STRING_CONTAINER,
} symbol_type;

struct Symbol
{
	symbol_type type;
	symbol_value value;
};

class Variable_handler
{
	std::map<std::string, Symbol> local;
	std::map<std::string, Symbol> Par;
	std::map<std::string, Symbol> Arg;

	Variable_handler();
	Variable_handler(Variable_handler const&);
	void operator=(Variable_handler const&);
public:
	static Variable_handler* get_instance();

	symbol_value& get_arg(std::string name);
	symbol_value& get_par(std::string name);
	symbol_value& get_local(std::string name);
};

#endif /* INC_VARIABLE_HANDLER_H_ */
