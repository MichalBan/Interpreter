#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

#include <variant>
#include <string>
#include "token_types.h"

typedef std::variant<std::string, int, float, bool> token_value;

class Token
{
public:
	token_type type;
	token_value value;
};

#endif /* SRC_TOKEN_H_ */
