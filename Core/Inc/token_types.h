#ifndef INC_TOKEN_TYPES_H_
#define INC_TOKEN_TYPES_H_

#include <map>

typedef enum
{
	TOKEN_ERROR, 	 		// wartość domyślna, zwrócenie jej przez lekser oznacza błąd
	TOKEN_COLON, 		 	// dwukropek po “setup”, “loop”, “finish”, alternatywach i pętlach np. while i > 1:
	TOKEN_IDENTIFIER,  		// identyfikator
	TOKEN_INT,  			// liczba całkowita
	TOKEN_FLOAT,			// liczba zmiennoprzecinkowa
	TOKEN_TRUE,  			// wartość logiczna “true”
	TOKEN_FALSE,  			// wartość logiczna “false”
	TOKEN_SETUP, 			// słowo kluczowe “setup”
	TOKEN_LOOP,  			// słowo kluczowe “loop”
	TOKEN_FINISH,  			// słowo kluczowe “finish”
	TOKEN_NEWLINE,  		// znak nowej linii oddzielający statementy
	TOKEN_DOT,  			// operator wyłuskania do zmiennych z Arg, Par lub do wywołania metody wektora
	TOKEN_COMA,  			// przecinek oddzielający wyrażenia np. przy inicjalizacji wektora
	TOKEN_LEFT_SQUARE, 		// lewy nawias kwadratowy służący do obsługi wektora
	TOKEN_RIGHT_SQUARE,  	// prawy nawias kwadratowy
	TOKEN_STRING,  			// dowolny ciąg znaków zaczynający się i kończący cudzysłowem
	TOKEN_IF,  				// słowo kluczowe “if” oznaczające alternatywę
	TOKEN_ELSEIF, 			// słowo kluczowe “elseif”
	TOKEN_ELSE,  			// słowo kluczowe “else”
	TOKEN_WHILE, 			// słowo kluczowe “while” oznaczające pętlę
	TOKEN_END,  			// słowo kluczowe “end” zamykające pętlę lub alternatywę
	TOKEN_OR, 				// znak specjalny “|” operator logiczny or
	TOKEN_AND, 				// znak specjalny “&” operator logiczny and
	TOKEN_EXCLAMATION, 		// znak specjalny “!” negacja logiczna
	TOKEN_ASSIGN, 			// znak specjalny “=”, operator przypisania
	TOKEN_GREATER_THAN, 	// znak specjalny “>”, służy do porównania zmiennych liczbowych
	TOKEN_GREATER_OR_EQUAL,	// znak specjalny “>=”, służy do porównania zmiennych liczbowych
	TOKEN_SMALLER_THAN,		// znak specjalny “<”, służy do porównania zmiennych liczbowych
	TOKEN_SMALLER_OR_EQUAL, // znak specjalny “<=”, służy do porównania zmiennych liczbowych
	TOKEN_EQUALS, 			// znak specjalny “==”, służy do porównania zmiennych liczbowych
	TOKEN_NOT_EQUAL, 		// znak specjalny “!=”, służy do porównania zmiennych liczbowych
	TOKEN_PLUS, 			// znak specjalny “+”, służy do operacji arytmetycznych
	TOKEN_MINUS, 			// znak specjalny “-”, służy do operacji arytmetycznych
	TOKEN_MULTIPLY, 		// znak specjalny “*”, służy do operacji arytmetycznych
	TOKEN_DIVIDE, 			// znak specjalny “/”, służy do operacji arytmetycznych
	TOKEN_POWER, 			// znak specjalny “^”, służy do operacji arytmetycznych
	TOKEN_MODULO, 			// znak specjalny “%”, służy do operacji arytmetycznych
	TOKEN_END_OF_FILE, 		// znak końca pliku
	TOKEN_LEFT_BRACKET, 	// znak specjalny początku grupowania “(”
	TOKEN_RIGHT_BRACKET, 	// znak specjalny końca grupowania “)”
}token_type;

static const std::map<char, token_type> token_chars
{
	{':', TOKEN_COLON},
	{'\n', TOKEN_NEWLINE},
	{',', TOKEN_COMA},
	{'.', TOKEN_DOT},
	{'[', TOKEN_LEFT_SQUARE},
	{']', TOKEN_RIGHT_SQUARE},
	{'|', TOKEN_OR},
	{'&', TOKEN_AND},
	{'+', TOKEN_PLUS},
	{'-', TOKEN_MINUS},
	{'*', TOKEN_MULTIPLY},
	{'/', TOKEN_DIVIDE},
	{'^', TOKEN_POWER},
	{'%', TOKEN_MODULO},
	{'(', TOKEN_LEFT_BRACKET},
	{')', TOKEN_RIGHT_BRACKET},
	{'\0', TOKEN_END_OF_FILE},
};

static const std::map<std::string, token_type> token_strings
{
	{"true", TOKEN_TRUE},
	{"false", TOKEN_FALSE},
	{"setup", TOKEN_SETUP},
	{"loop", TOKEN_LOOP},
	{"finish", TOKEN_FINISH},
	{"if", TOKEN_IF},
	{"elseif", TOKEN_ELSEIF},
	{"else", TOKEN_ELSE},
	{"while", TOKEN_WHILE},
	{"end", TOKEN_END},
};

typedef struct
{
	token_type single_char;
	token_type double_char;
}double_token;

static const std::map<char, double_token> token_double_chars
{
	{'<', {TOKEN_SMALLER_THAN, TOKEN_SMALLER_OR_EQUAL}},
	{'>', {TOKEN_GREATER_THAN, TOKEN_GREATER_OR_EQUAL}},
	{'=', {TOKEN_ASSIGN, TOKEN_EQUALS}},
	{'!', {TOKEN_EXCLAMATION, TOKEN_NOT_EQUAL}},
};

#endif /* INC_TOKEN_TYPES_H_ */
