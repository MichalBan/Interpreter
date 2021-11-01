#include "Parser.h"

Parser::Parser(Lexer *Lex, Transmitter *Trans)
{
	this->Lex = Lex;
	this->Trans = Trans;
}

While_statement Parser::parse_while()
{
	While_statement st;
	st.condition = parse_expression();
	assert_token(TOKEN_COLON, "colon after condition expression");
	get_next_token();
	st.while_body = parse_body();
	assert_token(TOKEN_END, "\"end\" after if body");
	get_next_token();
	return st;
}

void Parser::parse_elseif_content(If_statement &st)
{
	get_next_token();
	Expression *condition = new Expression(parse_expression());
	assert_token(TOKEN_COLON, "colon after condition expression");
	get_next_token();
	Body *if_body = new Body(parse_body());
	st.conditions.push_back(condition);
	st.if_bodies.push_back(if_body);
}

void Parser::parse_else_content(If_statement &st)
{
	get_next_token();
	assert_token(TOKEN_COLON, "colon after \"else\"");
	get_next_token();
	Body *if_body = new Body(parse_body());
	st.if_bodies.push_back(if_body);
}

void Parser::parse_if_content(If_statement &st)
{
	Expression *condition = new Expression(parse_expression());
	assert_token(TOKEN_COLON, "colon after condition expression");
	get_next_token();
	Body *if_body = new Body(parse_body());
	st.conditions.push_back(condition);
	st.if_bodies.push_back(if_body);
}

If_statement Parser::parse_if()
{
	If_statement st;

	parse_if_content(st);
	while (token_buffer.get_type() == TOKEN_ELSEIF)
	{
		parse_elseif_content(st);
	}
	if (token_buffer.get_type() == TOKEN_ELSE)
	{
		parse_else_content(st);
	}
	assert_token(TOKEN_END, "\"end\" after if body");
	get_next_token();

	return st;
}

void Parser::parse_variable_index(Variable &var)
{
	if (token_buffer.get_type() == TOKEN_LEFT_SQUARE)
	{
		get_next_token();
		var.index = new Expression(parse_expression());
		assert_token(TOKEN_RIGHT_SQUARE, "closing square bracket");
		get_next_token();
	}
	else
	{
		var.index = nullptr;
	}
}

void Parser::parse_member_selection_id(std::string &id)
{
	assert_token(TOKEN_DOT, "dot operator \".\"");
	get_next_token();
	assert_token(TOKEN_IDENTIFIER, "identifier");
	id = std::string(std::get<std::string>(token_buffer.get_value()));
	get_next_token();
}

void Parser::parse_variable_id(std::string& id, Variable &var)
{
	if (id == "Arg")
	{
		var.type = ASSIGNMENT_ARG;
		parse_member_selection_id(id);
	}
	else if (id == "Par")
	{
		var.type = ASSIGNMENT_PAR;
		parse_member_selection_id(id);
	}
	else
	{
		var.type = ASSIGNMENT_LOCAL;
	}

	var.id = std::string(id);
}

Variable Parser::parse_variable(std::string& id)
{
	Variable var;
	parse_variable_id(id, var);
	parse_variable_index(var);
	return var;
}

Assignment Parser::parse_assignment(std::string& id)
{
	Assignment st;
	st.var = parse_variable(id);
	assert_token(TOKEN_ASSIGN, "assignment operator \"=\"");
	get_next_token();
	st.value = new Expression(parse_expression());
	return st;
}

void Parser::report_error(const std::string message)
{
	Trans->report_error(message, token_buffer.get_line(),
			token_buffer.get_position());
}

void Parser::assert_token(token_type type, const std::string message)
{
	if (token_buffer.get_type() != type)
	{
		std::string msg = "expected " + message + "\n";
		report_error(msg);
	}
}

void Parser::parse_function_arguments(Function_call &f)
{
	if (token_buffer.get_type() != TOKEN_RIGHT_BRACKET)
	{
		f.arguments.push_back(new Expression(parse_expression()));
		while (token_buffer.get_type() == TOKEN_COMA)
		{
			get_next_token();
			f.arguments.push_back(new Expression(parse_expression()));
		}
	}
}

Function_call Parser::parse_function_call(std::string& id)
{
	Function_call f;
	f.id = std::string(id);
	get_next_token();
	parse_function_arguments(f);
	assert_token(TOKEN_RIGHT_BRACKET, "closing bracket");
	get_next_token();
	assert_token(TOKEN_NEWLINE, "new line");
	get_next_token();
	return f;
}

void Parser::parse_assignment_or_function_call(Statement &s)
{
	std::string id = std::get<std::string>(token_buffer.get_value());
	get_next_token();
	if (token_buffer.get_type() == TOKEN_LEFT_BRACKET)
	{
		s.type = STATEMENT_FUNCTION_CALL;
		s.content = parse_function_call(id);
	}
	else
	{
	    s.type = STATEMENT_ASSIGNMENT;
		s.content = parse_assignment(id);
	}
}

Statement Parser::parse_statement() //todo refactor
{
	Statement s{};
	switch (token_buffer.get_type())
	{
	case TOKEN_IDENTIFIER:
		parse_assignment_or_function_call(s);
		break;
	case TOKEN_WHILE:
		s.type = STATEMENT_WHILE;
		get_next_token();
		s.content = parse_while();
		break;
	case TOKEN_IF:
		s.type = STATEMENT_IF;
		get_next_token();
		s.content = parse_if();
		break;
	default:
		report_error("expected statement:\nidentifier, if, while\n");
		break;
	}
	return s;
}

bool Parser::is_token_statement_first()
{
	return token_buffer.get_type() == TOKEN_IDENTIFIER
			|| token_buffer.get_type() == TOKEN_WHILE
			|| token_buffer.get_type() == TOKEN_IF;
}

void Parser::skip_newlines()
{
	while (token_buffer.get_type() == TOKEN_NEWLINE)
	{
		get_next_token();
	}
}

Body Parser::parse_body()
{
	Body bod;
	while (is_token_statement_first())
	{
		Statement *st = new Statement(parse_statement());
		bod.statements.push_back(st);
		skip_newlines();
	}
	return bod;
}

void Parser::get_next_token()
{
	token_buffer = Lex->build_token();
	if (token_buffer.get_type() == TOKEN_ERROR)
	{
		Trans->report_error(std::get<std::string>(token_buffer.get_value()),
				token_buffer.get_line(), token_buffer.get_position());
	}
}

void Parser::parse_setup(Program& Prog)
{
	get_next_token();
	assert_token(TOKEN_SETUP, "\"setup\" keyword");
	get_next_token();
	assert_token(TOKEN_COLON, "colon after setup");
	get_next_token();
    skip_newlines();
	Prog.setup = parse_body();
}

void Parser::parse_loop(Program& Prog)
{
	assert_token(TOKEN_LOOP, "\"loop\" keyword");
	get_next_token();
	assert_token(TOKEN_COLON, "colon after loop");
	get_next_token();
    skip_newlines();
	Prog.loop = parse_body();
}

void Parser::parse_finish(Program& Prog)
{
	assert_token(TOKEN_FINISH, "\"finish\" keyword");
	get_next_token();
	assert_token(TOKEN_COLON, "colon after finish");
	get_next_token();
    skip_newlines();
	Prog.finish = parse_body();
}

Program Parser::parse_program()
{
	Program Prog;
	parse_setup(Prog);
	parse_loop(Prog);
	parse_finish(Prog);
	return Prog;
}