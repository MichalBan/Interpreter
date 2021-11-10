#include <Executor.h>

Symbol::~Symbol()
{

}

Executor::Executor(Transmitter *Trans)
{
	this->Trans = Trans;
	this->Fun = new Function_handler();
}

Executor::~Executor()
{
	delete Fun;
}

void Executor::execute(Program p)
{

}

void Executor::run_function(Statement *st)
{
	Function_call *fcall = std::get<Function_call*>(st->content);

	auto search = Fun->functions.find(fcall->id);
	if (search != Fun->functions.end())
	{
		search->second(fcall->arguments);
	}
	else
	{
		Trans->report_error(std::string("function " + fcall->id + " not found"),
				st->line, st->position);
	}

}
