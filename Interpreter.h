#include "Parser.h"

class Interpreter
{
private:
	static Interpreter* instance;
	Interpreter() = default;
	~Interpreter() = default;
	SyntaxTree* tree;
public:
	Interpreter(const Interpreter& obj) = delete;
	static Interpreter* getInterpreter()
	{
		if (instance == nullptr)
			instance = new Interpreter();
		return instance;
	};
	void initializer(SyntaxTree* tree_in)
	{
		this->tree = tree_in;
	}

	int Choice_TREE(SyntaxTree* st)
	{
		std::string st_T_type = st->getToken()->Type();
		if (st_T_type == Integer)
			return Integer_TREE(st);
		if (st_T_type == Identifier)
			return Identifier_TREE(st);

		if (st_T_type == PLUS)
			return PLUS_TREE(st);
		if (st_T_type == MINUS)
			return MINUS_TREE(st);

		if (st_T_type == MUL)
			return MUL_TREE(st);
		if (st_T_type == DIV)
			return DIV_TREE(st);
		if (st_T_type == PWD)
		{
			return PWD_TREE(st);
		}
		if (st_T_type == RESD)
			return RESD_TREE(st);
	}


	int string_to_nr(std::string nr_string)
	{
		int rez = 0;
		for (int i = 0; i < nr_string.size(); i++)
			rez = rez * 10 + nr_string[i] - '0';
		return rez;
	}

	int Integer_TREE(SyntaxTree* st)
	{
		return string_to_nr(st->getToken()->Value());
	}

	int Identifier_TREE(SyntaxTree* st)
	{

		///table of content
		return 0;
	}

	int PLUS_TREE(SyntaxTree* st)
	{
		return Choice_TREE(st->getLeftN()) + Choice_TREE(st->getRightN());
	}
	int MINUS_TREE(SyntaxTree* st)
	{
		return Choice_TREE(st->getLeftN()) - Choice_TREE(st->getRightN());
	}
	int MUL_TREE(SyntaxTree* st)
	{
		return Choice_TREE(st->getLeftN()) * Choice_TREE(st->getRightN());
	}
	int DIV_TREE(SyntaxTree* st)
	{
		return Choice_TREE(st->getLeftN()) / Choice_TREE(st->getRightN());
	}
	int PWD_TREE(SyntaxTree* st)
	{
		int nr = Choice_TREE(st->getLeftN());
		int power = Choice_TREE(st->getRightN());
		int rez = 1;
		for (int i = 1; i <= power; i++)
			rez = rez * nr;
		return rez;
	}
	int RESD_TREE(SyntaxTree* st)
	{
		return Choice_TREE(st->getLeftN()) % Choice_TREE(st->getRightN());
	}

};