#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include <variant>
#include <string>
#include "token_types.h"

typedef std::variant<std::string, int, float, bool> token_value;

class Token
{
	token_type type;
	token_value value;
    int line;
    int position;
public:
    ~Token();

	token_value get_value();
	void set_value(token_value value);
	token_type get_type();
	void set_type(token_type type);
	int get_line();
	void set_line(int line);
	int get_position();
	void set_position(int position);
};

#endif /* SRC_TOKEN_H_ */
