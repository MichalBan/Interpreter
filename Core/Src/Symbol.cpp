#include "Symbol.h"
#include "Transmitter.h"

Symbol::Symbol(int value)
{
	type = SYMBOL_INT;
	this->value = value;
}

Symbol::Symbol(float value)
{
	type = SYMBOL_FLOAT;
	this->value = value;
}

Symbol::Symbol(double value)
{
	type = SYMBOL_FLOAT;
	this->value = (float)value;
}

Symbol::Symbol(bool value)
{
	type = SYMBOL_BOOL;
	this->value = value;
}

Symbol::Symbol(std::string value)
{
	type = SYMBOL_STRING;
	this->value = value;
}

Symbol::Symbol(const char *value)
{
	type = SYMBOL_STRING;
	this->value = std::string(value);
}

Symbol::Symbol(std::initializer_list<Symbol> value)
{
	type = SYMBOL_CONTAINER;
	this->value = std::vector<Symbol>(value);
}

Symbol& Symbol::operator[](Symbol idx)
{
	if (idx.type != SYMBOL_INT)
	{
		Transmitter::report_error("index must be an integer");
	}
	int i = std::get<int>(idx.value);

	if (i < 0)
	{
		Transmitter::report_error("index must be positive");
	}

	if (type == SYMBOL_CONTAINER)
	{
		return std::get<std::vector<Symbol>>(value)[i];
	}
	else
	{
		Transmitter::report_error(
				"cannot perform [] operation on non container");
		return std::get<std::vector<Symbol>>(value)[0];
	}
}

Symbol Symbol::operator+(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return std::get<int>(this->value) + std::get<int>(other.value);
	case SYMBOL_FLOAT:
		return std::get<float>(this->value) + std::get<float>(other.value);
	case SYMBOL_BOOL:
		return std::get<bool>(this->value) + std::get<bool>(other.value);
	case SYMBOL_STRING:
		return std::get<std::string>(this->value) + std::get<std::string>(
				other.value);
	default:
		Transmitter::report_error("invalid type for addidion");
	}

	return 0;
}

Symbol Symbol::operator-(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return std::get<int>(this->value) - std::get<int>(other.value);
	case SYMBOL_FLOAT:
		return std::get<float>(this->value) - std::get<float>(other.value);
	default:
		Transmitter::report_error("invalid type for substraction");
	}

	return 0;
}

Symbol Symbol::operator&&(Symbol other)
{
	if (type != SYMBOL_BOOL || other.type != SYMBOL_BOOL)
	{
		Transmitter::report_error("operator and needs boolean expressions");
	}

	return std::get<bool>(this->value) && std::get<bool>(other.value);
}

Symbol Symbol::operator||(Symbol other)
{
	if (type != SYMBOL_BOOL || other.type != SYMBOL_BOOL)
	{
		Transmitter::report_error("operator or needs boolean expressions");
	}

	return std::get<bool>(this->value) || std::get<bool>(other.value);
}

Symbol Symbol::operator!()
{
	if (type != SYMBOL_BOOL)
	{
		Transmitter::report_error("operator ! needs boolean expressions");
	}

	return !(std::get<bool>(this->value));
}

Symbol Symbol::operator>(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) > std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (std::get<float>(this->value) > std::get<float>(other.value));
	default:
		Transmitter::report_error("invalid type for comparison");
	}

	return 0;
}

Symbol Symbol::operator>=(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) >= std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (std::get<float>(this->value) >= std::get<float>(other.value));
	default:
		Transmitter::report_error("invalid type for comparison");
	}

	return 0;
}

Symbol Symbol::operator<(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) < std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (std::get<float>(this->value) < std::get<float>(other.value));
	default:
		Transmitter::report_error("invalid type for comparison");
	}

	return 0;
}

Symbol Symbol::operator<=(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) <= std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (std::get<float>(this->value) <= std::get<float>(other.value));
	default:
		Transmitter::report_error("invalid type for comparison");
	}

	return 0;
}

Symbol Symbol::operator==(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) == std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (std::get<float>(this->value) == std::get<float>(other.value));
	case SYMBOL_BOOL:
		return (std::get<bool>(this->value) == std::get<bool>(other.value));
	default:
		Transmitter::report_error("invalid type for comparison");
	}

	return 0;
}

Symbol Symbol::operator!=(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) != std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (std::get<float>(this->value) != std::get<float>(other.value));
	case SYMBOL_BOOL:
		return (std::get<bool>(this->value) != std::get<bool>(other.value));
	default:
		Transmitter::report_error("invalid type for comparison");
	}

	return 0;
}

Symbol Symbol::operator-()
{
	switch (type)
	{
	case SYMBOL_INT:
		return (-std::get<int>(this->value));
	case SYMBOL_FLOAT:
		return (-std::get<float>(this->value));
	default:
		Transmitter::report_error("invalid type for minus unary operator");
	}

	return 0;
}

Symbol Symbol::operator*(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) * std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (std::get<float>(this->value) * std::get<float>(other.value));
	default:
		Transmitter::report_error("invalid type for multiplication");
	}

	return 0;
}

Symbol Symbol::operator/(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (std::get<int>(this->value) / std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return(std::get<float>(this->value) / std::get<float>(other.value));
	default:
		Transmitter::report_error("invalid type for multiplication");
	}

	return 0;
}

Symbol Symbol::operator%(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return(std::get<int>(this->value) % std::get<int>(other.value));
	default:
		Transmitter::report_error("invalid type for multiplication");
	}

	return 0;
}

Symbol Symbol::operator^(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		return (int)pow(std::get<int>(this->value), std::get<int>(other.value));
	case SYMBOL_FLOAT:
		return (float)pow(std::get<float>(this->value), std::get<float>(other.value));
	default:
		Transmitter::report_error("invalid type for multiplication");
	}

	return 0;
}


bool Symbol::get_bool()
{
	assert_type(SYMBOL_BOOL);
	return std::get<bool>(value);
}

void Symbol::assert_types(const Symbol &other)
{
	if (type != other.type)
	{
		Transmitter::report_error("types mismatch");
	}
}

void Symbol::assert_type(symbol_type type)
{
	if(this->type != type)
	{
		Transmitter::report_error(std::string("")); //todo message
	}
}

void Symbol::resize(int size)
{
	std::vector<Symbol> vec = std::get<std::vector<Symbol>>(value);
	if(vec.size() < (unsigned int)size)
	{
		vec.reserve(size);
	}
}

void Symbol::round()
{
	if(type == SYMBOL_INT)
	{
		return;
	}
	else if(type == SYMBOL_FLOAT)
	{
		float result = std::get<float>(value);
		type = SYMBOL_INT;
		value = (int)result;
	}
	else
	{
		Transmitter::report_error(std::string("can not round a non float"));
	}
}

void Symbol::floatify()
{
	if(type == SYMBOL_INT)
	{
		float result = std::get<int>(value);
		type = SYMBOL_FLOAT;
		value = (float)result;
	}
	else if(type == SYMBOL_FLOAT)
	{
		return;
	}
	else
	{
		Transmitter::report_error(std::string("can not floatify a non int"));
	}
}
