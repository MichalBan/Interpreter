#ifndef PARSER_H_
#define PARSER_H_

#include "Expression.h"
#include "Statement.h"
#include "Lexer.h"
#include "Transmitter.h"

class Program
{
public:
	~Program();
	Body *setup;
	Body *loop;
	Body *finish;
};

class Parser
{
	Token token_buffer;

	SINGLETON(Parser)

	Body* parse_body();
	bool is_token_statement_first();
	void skip_newlines();
	Statement* parse_statement();
	While_statement* parse_while();
	If_statement* parse_if();
	Assignment* parse_assignment(Variable* var);
	Function_call* parse_function_call(std::string &id);
	Method_call* parse_method_call(Variable* var);
	Variable* parse_variable(std::string &id);
	void get_next_token();
	void assert_token(token_type type, const std::string message);
	void parse_variable_index(Variable *var);
	Expression* parse_expression();
	void parse_variable_id(std::string &id, Variable *var);
	void parse_member_selection_id(std::string &id);
	void parse_else_content(If_statement *st);
	void parse_elseif_content(If_statement *st);
	void parse_if_content(If_statement *st);
	Primal_expression* parse_primal_expression();
	Priority_expression* parse_priority_expression();
	Unary_expression* parse_unary_expression();
	Power_expression* parse_power_expression();
	Multiply_expression* parse_multiply_expression();
	Sum_expression* parse_sum_expression();
	Relation_expression* parse_relation_expression();
	Compare_expression* parse_compare_expression();
	And_expression* parse_and_expression();
	bool match_compare_operator(Compare_expression *exp);
	bool match_relation_operator(Relation_expression *exp);
	bool match_sum_operator(Sum_expression *exp);
	bool match_multiply_operator(Multiply_expression *exp);
	bool match_unary_operator(Unary_expression *exp);
	Expression* parse_nested_expression();
	void parse_function_arguments(Function_call *f);
	void parse_identifier_statement(Statement *s);
	void parse_variable_or_function_call(Primal_expression *exp);
	void parse_setup(Program *Prog);
	void parse_loop(Program *Prog);
	void parse_finish(Program *Prog);
public:
	static Program* parse_program();
	void parse_variable_statement(std::string id, Statement *s);
};

#endif /* PARSER_H_ */
