#ifndef INC_SYMBOL_H_
#define INC_SYMBOL_H_

#include <vector>
#include <variant>
#include <string>
#include <cmath>

class Symbol;

typedef std::variant<int, float, bool, std::string, std::vector<Symbol>> symbol_value;

typedef enum
{
	SYMBOL_INT, SYMBOL_FLOAT, SYMBOL_BOOL, SYMBOL_STRING, SYMBOL_CONTAINER,
} symbol_type;

class Symbol
{
public:
	symbol_type type;
	symbol_value value;

	Symbol() = default;
	Symbol(int value);
	Symbol(float value);
	Symbol(double value);
	Symbol(bool value);
	Symbol(std::string value);
	Symbol(const char *value);
	Symbol(std::initializer_list<Symbol> value);

	Symbol& operator[](Symbol idx);
	Symbol operator&&(Symbol other);
	Symbol operator||(Symbol other);
	Symbol operator!();
	Symbol operator>(Symbol other);
	Symbol operator>=(Symbol other);
	Symbol operator<(Symbol other);
	Symbol operator<=(Symbol other);
	Symbol operator==(Symbol other);
	Symbol operator!=(Symbol other);
	Symbol operator+(Symbol other);
	Symbol operator-(Symbol other);
	Symbol operator*(Symbol other);
	Symbol operator/(Symbol other);
	Symbol operator%(Symbol other);
	Symbol operator^(Symbol other);
	Symbol operator-();
	bool get_bool();
	void assert_types(const Symbol &other);
	void assert_type(symbol_type type);

	void resize(int size);
	void round();
	void floatify();
};

#endif /* INC_SYMBOL_H_ */
