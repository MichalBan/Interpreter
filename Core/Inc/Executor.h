#ifndef INC_EXECUTOR_H_
#define INC_EXECUTOR_H_

#include "Parser.h"

typedef std::variant< int, float, bool, std::string, std::vector<std::string>,
		std::vector<int>, std::vector<float>, std::vector<bool>> symbol_value;

typedef void (*function_pointer)(void); // todo argumenty funkcji

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

class Symbol
{
public:
	~Symbol();
	symbol_type type;
	symbol_value value;
};

class Executor
{
	std::vector<Symbol*> variables;
	std::map<std::string, function_pointer> functions;

public:
	Executor();
	void execute(Program p);
	virtual ~Executor();
};

#endif /* INC_EXECUTOR_H_ */
