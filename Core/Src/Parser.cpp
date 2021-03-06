#include "Parser.h"

Program::~Program()
{
	delete setup;
	delete loop;
	delete finish;
}

Parser::Parser()
{

}

While_statement* Parser::parse_while()
{
	auto st = new While_statement();
	st->condition = parse_expression();
	assert_token(TOKEN_NEWLINE, "line break after condition expression");
	get_next_token();
	st->while_body = parse_body();
	assert_token(TOKEN_END, "\"end\" after if body");
	get_next_token();
	return st;
}

void Parser::parse_elseif_content(If_statement *st)
{
	get_next_token();
	st->conditions.push_back(parse_expression());
	assert_token(TOKEN_NEWLINE, "line break after condition expression");
	get_next_token();
	st->if_bodies.push_back(parse_body());
}

void Parser::parse_else_content(If_statement *st)
{
	get_next_token();
	assert_token(TOKEN_NEWLINE, "line break after \"else\"");
	get_next_token();
	st->if_bodies.push_back(parse_body());
}

void Parser::parse_if_content(If_statement *st)
{
	st->conditions.push_back(parse_expression());
	assert_token(TOKEN_NEWLINE, "line break after condition expression");
	get_next_token();
	st->if_bodies.push_back(parse_body());
}

If_statement* Parser::parse_if()
{
	auto st = new If_statement();

	parse_if_content(st);
	while (token_buffer.type == TOKEN_ELSEIF)
	{
		parse_elseif_content(st);
	}
	if (token_buffer.type == TOKEN_ELSE)
	{
		parse_else_content(st);
	}
	assert_token(TOKEN_END, "\"end\" after if body");
	get_next_token();

	return st;
}

void Parser::parse_variable_index(Variable *var)
{
	if (token_buffer.type == TOKEN_LEFT_SQUARE)
	{
		get_next_token();
		var->index = parse_expression();
		assert_token(TOKEN_RIGHT_SQUARE, "closing square bracket");
		get_next_token();
	}
	else
	{
		var->index = nullptr;
	}
}

void Parser::parse_member_selection_id(std::string &id)
{
	assert_token(TOKEN_COLON, "colon operator \":\"");
	get_next_token();
	assert_token(TOKEN_IDENTIFIER, "identifier");
	id = std::string(std::get<std::string>(token_buffer.value));
	get_next_token();
}

void Parser::parse_variable_id(std::string &id, Variable *var)
{
	if (id == "Arg")
	{
		var->type = VARIABLE_ARG;
		parse_member_selection_id(id);
	}
	else if (id == "Par")
	{
		var->type = VARIABLE_PAR;
		parse_member_selection_id(id);
	}
	else
	{
		var->type = VARIABLE_LOCAL;
	}

	var->id = std::string(id);
}

Variable* Parser::parse_variable(std::string &id)
{
	auto var = new Variable();
	parse_variable_id(id, var);
	parse_variable_index(var);
	return var;
}

Assignment* Parser::parse_assignment(Variable* var)
{
	auto st = new Assignment();
	st->var = var;
	st->value = parse_expression();
	return st;
}

void Parser::assert_token(token_type type, const std::string message)
{
	if (token_buffer.type != type)
	{
		std::string msg = "expected " + message;
		Transmitter::report_error(msg);
	}
}

void Parser::parse_function_arguments(Function_call *f)
{
	if (token_buffer.type != TOKEN_RIGHT_BRACKET)
	{
		f->arguments.push_back(parse_expression());
		while (token_buffer.type == TOKEN_COMA)
		{
			get_next_token();
			f->arguments.push_back(parse_expression());
		}
	}
}

Function_call* Parser::parse_function_call(std::string &id)
{
	auto f = new Function_call();
	f->id = std::string(id);
	f->line = Position_counter::get_instance().get_line();
	f->position = Position_counter::get_instance().get_position();
	get_next_token();
	parse_function_arguments(f);
	assert_token(TOKEN_RIGHT_BRACKET, "closing bracket");
	get_next_token();
	return f;
}

Method_call* Parser::parse_method_call(Variable* var)
{
	auto m = new Method_call();
	m->vector = var;
	assert_token(TOKEN_IDENTIFIER, "method identifier");
	std::string id = std::get<std::string>(token_buffer.value);
	get_next_token();
	assert_token(TOKEN_LEFT_BRACKET, "opening bracket");
	m->call = parse_function_call(id);
	return m;
}

void Parser::parse_variable_statement(std::string id, Statement *s)
{
	auto var = parse_variable(id);
	if (token_buffer.type == TOKEN_ASSIGN)
	{
		s->type = STATEMENT_ASSIGNMENT;
		get_next_token();
		s->content = parse_assignment(var);
	}
	else
	{
		assert_token(TOKEN_DOT, "method call or assignment");
		s->type = STATEMENT_METHOD_CALL;
		get_next_token();
		s->content = parse_method_call(var);
	}
}

void Parser::parse_identifier_statement(Statement *s)
{
	std::string id = std::get<std::string>(token_buffer.value);
	get_next_token();
	if (token_buffer.type == TOKEN_LEFT_BRACKET)
	{
		s->type = STATEMENT_FUNCTION_CALL;
		s->content = parse_function_call(id);
	}
	else
	{
		parse_variable_statement(id, s);
	}
}

Statement* Parser::parse_statement() //todo refactor
{
	auto s = new Statement();
	switch (token_buffer.type)
	{
	case TOKEN_IDENTIFIER:
		parse_identifier_statement(s);
		break;
	case TOKEN_WHILE:
		s->type = STATEMENT_WHILE;
		get_next_token();
		s->content = parse_while();
		break;
	case TOKEN_IF:
		s->type = STATEMENT_IF;
		get_next_token();
		s->content = parse_if();
		break;
	default:
		Transmitter::report_error("expected statement: identifier, if, while");
		break;
	}
	return s;
}

bool Parser::is_token_statement_first()
{
	return token_buffer.type == TOKEN_IDENTIFIER
			|| token_buffer.type == TOKEN_WHILE
			|| token_buffer.type == TOKEN_IF;
}

void Parser::skip_newlines()
{
	while (token_buffer.type == TOKEN_NEWLINE)
	{
		get_next_token();
	}
}

Body* Parser::parse_body()
{
	auto bod = new Body();
	while (is_token_statement_first())
	{
		bod->statements.push_back(parse_statement());
		skip_newlines();
	}
	return bod;
}

void Parser::get_next_token()
{
	token_buffer = Lexer::build_token();
	if (token_buffer.type == TOKEN_ERROR)
	{
		Transmitter::report_error(std::get<std::string>(token_buffer.value));
	}
}

void Parser::parse_setup(Program *Prog)
{
	get_next_token();
	assert_token(TOKEN_SETUP, "\"setup\" keyword");
	get_next_token();
	assert_token(TOKEN_NEWLINE, "line break after setup");
	get_next_token();
	skip_newlines();
	Prog->setup = parse_body();
}

void Parser::parse_loop(Program *Prog)
{
	assert_token(TOKEN_LOOP, "\"loop\" keyword");
	get_next_token();
	assert_token(TOKEN_NEWLINE, "line break after loop");
	get_next_token();
	skip_newlines();
	Prog->loop = parse_body();
}

void Parser::parse_finish(Program *Prog)
{
	assert_token(TOKEN_FINISH, "\"finish\" keyword");
	get_next_token();
	assert_token(TOKEN_NEWLINE, "line break after finish");
	get_next_token();
	skip_newlines();
	Prog->finish = parse_body();
}

Program* Parser::parse_program()
{
	static Parser Par;
	auto Prog = new Program();
	Par.parse_setup(Prog);
	Par.parse_loop(Prog);
	Par.parse_finish(Prog);
	Par.assert_token(TOKEN_END_OF_FILE, "end of file");
	return Prog;
}
