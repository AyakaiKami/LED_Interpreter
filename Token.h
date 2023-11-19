#pragma once
#include <string>
#include <iostream>
///Defining Token types

#define Identifier "Identifier"
#define Integer "Integer"
#define EQ "EQ"
#define PLUS "PLUS"
#define MINUS "MINUS"
#define DIV "DIV"
#define MUL "MUL"
#define PWD "PWD"
#define RESD "RESD"
#define LPAR "LPAR"
#define RPAR "RPAR"
class Token
{
private:
	std::string type;
	std::string value;

public:
	Token(const std::string type_in, std::string value_in = "")
	{
		this->type = type_in;
		this->value = value_in;
	};
	~Token() = default;
	void PrintToken()
	{
		std::cout << this->type;
		if (value.compare("") != 0)
		{
			std::cout << ":" << this->value;
		}
	};
	std::string Type()
	{
		return this->type;
	}
	std::string Value()
	{
		return this->value;
	}
};
