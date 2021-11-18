#include <Lexer.h>

Lexer::Lexer()
{
	code = new Source();
	// needs to start with whitespace in buffer
	char_buffer = ' ';
}

Lexer::~Lexer()
{
	delete code;
}

bool Lexer::match_single_char()
{
	auto result = token_chars.find(char_buffer);
	if (result != token_chars.end())
	{
		product.type = result->second;
		char_buffer = code->receive_code_char();
		return true;
	}
	return false;
}

bool Lexer::match_double_char()
{
	auto result = token_double_chars.find(char_buffer);
	if (result != token_double_chars.end())
	{
		char_buffer = code->receive_code_char();
		if (char_buffer == '=')
		{
			product.type = result->second.double_char;
			char_buffer = code->receive_code_char();
		}
		else
		{
			product.type = result->second.single_char;
		}
		return true;
	}
	return false;
}

void Lexer::build_word(std::string &word)
{
	do
	{
		word.push_back(char_buffer);
		char_buffer = code->receive_code_char();
	} while (isalnum(char_buffer) || char_buffer == '_');
}

void Lexer::match_keyword_or_id(std::string &word)
{
	auto result = token_strings.find(word);
	if (result != token_strings.end())
	{
		product.type = result->second;
	}
	else
	{
		product.type = TOKEN_IDENTIFIER;
		product.value = std::string(word);
	}
}

bool Lexer::build_keyword_or_id()
{
	if (isalpha(char_buffer))
	{
		std::string word;
		build_word(word);
		match_keyword_or_id(word);
		return true;
	}
	return false;
}

void Lexer::build_int(std::string &word)
{
	do
	{
		word.push_back(char_buffer);
		char_buffer = code->receive_code_char();
	} while (isdigit(char_buffer));
}

void Lexer::match_int_or_float(std::string &word)
{
	if (char_buffer != '.')
	{
		product.type = TOKEN_INT;
		product.value = std::stoi(word);
	}
	else
	{
		build_int(word);
		product.type = TOKEN_FLOAT;
		product.value = std::stof(word);
	}
}

bool Lexer::build_int_or_float()
{
	if (isdigit(char_buffer) && char_buffer != '0')
	{
		std::string word;
		build_int(word);
		match_int_or_float(word);
		return true;
	}
	return false;
}

bool Lexer::build_0_int_or_float()
{
	if (char_buffer == '0')
	{
		char_buffer = code->receive_code_char();
		if (char_buffer == '.')
		{
			std::string word;
			build_int(word);
			product.type = TOKEN_FLOAT;
			product.value = std::stof(word);
		}
		else
		{
			product.type = TOKEN_INT;
			product.value = 0;
		}
		return true;
	}
	return false;
}

void Lexer::match_escape_char(std::string &word)
{
	char true_char;
	switch (char_buffer)
	{
	case 'n':
		true_char = '\n';
		break;
	case '\'':
		true_char = '\'';
		break;
	case '\\':
		true_char = '\\';
		break;
	case '\"':
		true_char = '\"';
		break;
	case 'r':
		true_char = '\r';
		break;
	case 't':
		true_char = '\t';
		break;
	case 'b':
		true_char = '\b';
		break;
	case 'f':
		true_char = '\f';
		break;
	case 'v':
		true_char = '\v';
		break;
	default:
		return;
	}
	word.pop_back();
	word.push_back(true_char);
}

void Lexer::add_string_char(std::string &word)
{
	if (word.back() == '\\')
	{
		match_escape_char(word);
	}
	else
	{
		word.push_back(char_buffer);
	}
	char_buffer = code->receive_code_char();
}

void Lexer::build_string_content(std::string &word)
{
	char_buffer = code->receive_code_char();
	while (!(char_buffer == '\"' && word.back() != '\\'))
	{
		add_string_char(word);
	}
	char_buffer = code->receive_code_char();
}

bool Lexer::build_string()
{
	if (char_buffer == '\"')
	{
		std::string word;
		build_string_content(word);
		product.type = TOKEN_STRING;
		product.value = std::string(word);
		return true;
	}
	return false;
}

bool Lexer::build_token_value()
{
	return match_single_char() || match_double_char() || build_keyword_or_id()
			|| build_int_or_float() || build_0_int_or_float() || build_string();
}

Token Lexer::build_token()
{
	static Lexer lex;
	lex.get_working_char();
	lex.product.line = lex.code->get_line();
	lex.product.position = lex.code->get_position();

	if (lex.build_token_value())
	{
		return lex.product;
	}

	return lex.product;
}

void Lexer::skip_comment()
{
	while (char_buffer == '#')
	{
		while (char_buffer != '\n')
		{
			char_buffer = code->receive_code_char();
		}
		char_buffer = code->receive_code_char();
	}
}

void Lexer::skip_whitespace()
{
	while (isspace(char_buffer) && char_buffer != '\n')
	{
		char_buffer = code->receive_code_char();
	}
}

bool Lexer::is_invalid_char()
{
	return (isspace(char_buffer) && char_buffer != '\n') || char_buffer == '#';
}

void Lexer::get_working_char()
{
	while (is_invalid_char())
	{
		skip_comment();
		skip_whitespace();
	}
}
