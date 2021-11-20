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
		std::get<int>(this->value) += std::get<int>(other.value);
		break;
	case SYMBOL_FLOAT:
		std::get<float>(this->value) += std::get<float>(other.value);
		break;
	case SYMBOL_BOOL:
		std::get<bool>(this->value) += std::get<bool>(other.value);
		break;
	case SYMBOL_STRING:
		std::get<std::string>(this->value) += std::get<std::string>(
				other.value);
		break;
	default:
		Transmitter::report_error("invalid type for addidion");
		break;
	}

	return *this;
}

Symbol Symbol::operator-(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		std::get<int>(this->value) -= std::get<int>(other.value);
		break;
	case SYMBOL_FLOAT:
		std::get<float>(this->value) -= std::get<float>(other.value);
		break;
	default:
		Transmitter::report_error("invalid type for substraction");
		break;
	}

	return *this;
}

Symbol Symbol::operator&&(Symbol other)
{
	if (type != SYMBOL_BOOL || other.type != SYMBOL_BOOL)
	{
		Transmitter::report_error("operator and needs boolean expressions");
	}

	std::get<bool>(this->value) = std::get<bool>(this->value)
			&& std::get<bool>(other.value);

	return *this;
}

Symbol Symbol::operator||(Symbol other)
{
	if (type != SYMBOL_BOOL || other.type != SYMBOL_BOOL)
	{
		Transmitter::report_error("operator or needs boolean expressions");
	}

	std::get<bool>(this->value) = std::get<bool>(this->value)
			|| std::get<bool>(other.value);

	return *this;
}

Symbol Symbol::operator!()
{
	if (type != SYMBOL_BOOL)
	{
		Transmitter::report_error("operator ! needs boolean expressions");
	}

	std::get<bool>(this->value) = !(std::get<bool>(this->value));

	return *this;
}

Symbol Symbol::operator>(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) > std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) > std::get<float>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for comparison");
		break;
	}

	return *this;
}

Symbol Symbol::operator>=(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) >= std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) >= std::get<float>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for comparison");
		break;
	}

	return *this;
}

Symbol Symbol::operator<(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) < std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) < std::get<float>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for comparison");
		break;
	}

	return *this;
}

Symbol Symbol::operator<=(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) <= std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) <= std::get<float>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for comparison");
		break;
	}

	return *this;
}

Symbol Symbol::operator==(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) == std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) == std::get<float>(other.value));
		break;
	case SYMBOL_BOOL:
		this->value = (std::get<bool>(this->value) == std::get<bool>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for comparison");
		break;
	}

	return *this;
}

Symbol Symbol::operator!=(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) != std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) != std::get<float>(other.value));
		break;
	case SYMBOL_BOOL:
		this->value = (std::get<bool>(this->value) != std::get<bool>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for comparison");
		break;
	}

	return *this;
}

Symbol Symbol::operator-()
{
	switch (type)
	{
	case SYMBOL_INT:
		std::get<int>(this->value) = (-std::get<int>(this->value));
		break;
	case SYMBOL_FLOAT:
		std::get<float>(this->value) = (-std::get<float>(this->value));
		break;
	default:
		Transmitter::report_error("invalid type for minus unary operator");
		break;
	}

	return *this;
}

Symbol Symbol::operator*(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) * std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) * std::get<float>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for multiplication");
		break;
	}

	return *this;
}

Symbol Symbol::operator/(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) / std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (std::get<float>(this->value) / std::get<float>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for multiplication");
		break;
	}

	return *this;
}

Symbol Symbol::operator%(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (std::get<int>(this->value) % std::get<int>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for multiplication");
		break;
	}

	return *this;
}

Symbol Symbol::operator^(Symbol other)
{
	assert_types(other);

	switch (type)
	{
	case SYMBOL_INT:
		this->value = (int)pow(std::get<int>(this->value), std::get<int>(other.value));
		break;
	case SYMBOL_FLOAT:
		this->value = (float)pow(std::get<float>(this->value), std::get<float>(other.value));
		break;
	default:
		Transmitter::report_error("invalid type for multiplication");
		break;
	}

	return *this;
}

void Symbol::assert_types(const Symbol &other)
{
	if (type != other.type)
	{
		Transmitter::report_error("types mismatch");
	}
}

