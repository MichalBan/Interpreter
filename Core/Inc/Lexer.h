#ifndef INC_LEXER_H_
#define INC_LEXER_H_

#include "Transmitter.h"
#include "Token.h"

class Lexer
{
	char char_buffer;
	Token product;

	Lexer();
	Lexer(Lexer const&);
	void operator=(Lexer const&);

	void get_working_char();
	bool match_single_char();
	bool match_double_char();
	bool build_keyword_or_id();
	void build_word(std::string &word);
	void match_keyword_or_id(std::string& word);
	bool build_int_or_float();
	void build_int(std::string &word);
	void match_int_or_float(std::string& word);
	bool build_0_int_or_float();
	bool build_string();
	void skip_comment();
	void skip_whitespace();
	bool is_invalid_char();
	void match_escape_char(std::string &word);
	void build_string_content(std::string &word);
	void add_string_char(std::string &word);
	bool build_token_value();
public:
	static Token build_token();
};

#endif /* INC_LEXER_H_ */
