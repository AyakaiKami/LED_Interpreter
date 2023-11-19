#include "Token.h"


#define FACT "FACT"
#define TERM "TERM"
#define EXP "EXP"




class SyntaxTree
{
private:
	Token* info;
	std::string type;
	SyntaxTree* LeftSubST;
	SyntaxTree* RightSubST;
public:
	SyntaxTree() = default;
	SyntaxTree(Token* info_in, std::string type_in, SyntaxTree* left_in = NULL, SyntaxTree* right_in = NULL)
	{
		this->info = info_in;
		this->type = type_in;
		this->LeftSubST = left_in;
		this->RightSubST = right_in;
	};
	~SyntaxTree() = default;
	void SetLeftN(SyntaxTree* Left_set)
	{
		this->LeftSubST = Left_set;
	};
	void SetRightN(SyntaxTree* Right_set)
	{
		this->RightSubST = Right_set;
	};
	void Print()
	{
		std::cout << "( ";
		this->info->PrintToken();
		if (this->LeftSubST != NULL)
		{
			std::cout << " ";
			this->LeftSubST->Print();
		}
		if (this->RightSubST != NULL)
		{
			std::cout << " ";
			this->RightSubST->Print();
		}
		std::cout << " )";
		//std::cout << "\n";
	};
	std::string sType()
	{
		return this->type;

	};
	Token* getToken()
	{
		return this->info;
	};
	SyntaxTree* getLeftN()
	{
		return this->LeftSubST;
	};
	SyntaxTree* getRightN()
	{
		return this->RightSubST;
	};
};

