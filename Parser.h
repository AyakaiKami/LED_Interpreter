#include "Lexer.h"
#include "SyntaxTree.h"
#include <stack>
class Parser
{
private:
	std::vector<Token*> List_Tokens;
	Token* cToken;
	int size_List;
	SyntaxTree* tree;
	std::stack<SyntaxTree*>stack;
	static Parser* instance;
	int indexList;
	Parser() = default;
	~Parser() = default;
public:
	Parser(const Parser& obj) = delete;
	static Parser* getParser()
	{
		if (instance == NULL)
			instance = new Parser();
		return instance;
	};
	void Advance()
	{
		this->indexList++;
		this->cToken = this->List_Tokens[this->indexList];
		//std::cout << "[TokenList] Getting " << this->cToken->Type() << "\n";
	};
	void TokenParser(std::vector<Token*> List_Tokens_in)
	{
		this->indexList = -1;
		this->List_Tokens = List_Tokens_in;
		this->size_List = List_Tokens_in.size();
		//std::cout << "Size of list is " << size_List << "\n";
		this->stack.push(nullptr);
		this->Advance();
		//this->tree = Term();
		this->tree = Make();
	};
	void mpop(SyntaxTree*& rezpop)
	{
		rezpop = this->stack.top();
		this->stack.pop();
	}
	std::string LookAhead()///returns the type of token that is next
	{
		if (this->indexList + 1 < this->size_List)
			return this->List_Tokens[this->indexList + 1]->Type();
		//std::cout << "No words left\n";
		return "";
	};
	SyntaxTree* Make()
	{
		SyntaxTree* rezpop = nullptr;///pop() result
		this->stack.push(rezpop);///end
		while (this->indexList + 1 < this->size_List)
		{
			this->Advance();
			std::cout << this->indexList << "\n";
			this->mpop(rezpop);
			if (this->cToken->Type() == Identifier || this->cToken->Type() == Integer)
			{
				std::cout << "[caseP] Token is ident|nr ";
				if (rezpop == nullptr)
				{
					std::cout << " HStack NULL ";
					if (this->LookAhead() == PLUS || this->LookAhead() == MINUS)
					{
						std::cout << "LookAhead +|-\n";
						this->stack.push(rezpop);
						SyntaxTree* st;
						st = new SyntaxTree(this->cToken, EXP);
						this->stack.push(st);
						continue;
					}
					if (this->LookAhead() == MUL || this->LookAhead() == DIV || this->LookAhead() == PWD || this->LookAhead() == RESD)
					{
						std::cout << "LookAhead * | / | % | ^ \n";
						this->stack.push(rezpop);
						SyntaxTree* st;
						st = new SyntaxTree(this->cToken, FACT);
						this->stack.push(st);
						continue;
					}
				}
				else
					if (rezpop->sType() == FACT)
					{
						std::cout << " HStack FACT \n";
						SyntaxTree* st = new SyntaxTree(this->cToken, FACT);
						rezpop->SetRightN(st);
						this->stack.push(rezpop);
						continue;
					}
					else
						if (rezpop->sType() == EXP)
						{
							std::cout << " HStack EXP ";
							if (this->LookAhead() == MUL || this->LookAhead() == DIV || this->LookAhead() == PWD || this->LookAhead() == RESD)
							{
								std::cout << "LookAhead * | / | % | ^ \n";
								this->stack.push(rezpop);
								SyntaxTree* st = new SyntaxTree(this->cToken, FACT);
								this->stack.push(st);
								continue;
							}
							else
							{
								std::cout << "LookAhead +|-\n";
								SyntaxTree* st = new SyntaxTree(this->cToken, EXP);
								rezpop->SetRightN(st);
								this->stack.push(rezpop);
								continue;
							}
						}
			}
			if (this->cToken->Type() == MUL || this->cToken->Type() == DIV || this->cToken->Type() == PWD || this->cToken->Type() == RESD)
			{
				std::cout << "[caseP] Token is * | / | % | ^ ";
				if (rezpop->sType() == FACT)
				{
					std::cout << " HStack FACT\n";
					SyntaxTree* st = new SyntaxTree(this->cToken, FACT, rezpop);
					this->stack.push(st);
					continue;
				}
			}
			if (this->cToken->Type() == PLUS || this->cToken->Type() == MINUS)
			{
				std::cout << "[caseP] Token is + | - ";
				if (rezpop->sType() == EXP || rezpop->sType() == FACT)
				{
					std::cout << "Hstack EXP | FACT \n";
					SyntaxTree* st = new SyntaxTree(this->cToken, EXP, rezpop);
					this->stack.push(st);
					continue;
				}

			}
		}



		SyntaxTree* rez = nullptr;
		this->mpop(rez);
		while (rez != nullptr)
		{
			//rez->Print();
			this->mpop(rezpop);
			if (rezpop == nullptr)
			{
				break;
			}
			//rezpop->Print();
			if (rez->sType() == FACT)
			{
				if (rezpop->sType() == EXP)
				{
					rezpop->SetRightN(rez);
					this->stack.push(rezpop);
				}
			}
			if (rez->sType() == EXP)
			{
				if (rezpop->sType() == EXP)
				{
					rezpop->SetRightN(rez);
					this->stack.push(rezpop);
				}
			}
			this->mpop(rez);
		}
		//rez->Print();
		///std::cout << "this stopped\n";
		return rez;
	};

	SyntaxTree* Term()
	{
		std::cout << "here\n";
		if (this->cToken->Type() == Identifier || this->cToken->Type() == Integer)
		{
			if (this->LookAhead() == PWD)
			{
				this->stack.push(new SyntaxTree(this->cToken, TERM));
				this->Advance();
				return this->Term();
			}
			else
			{
				return new SyntaxTree(this->cToken, TERM);
			}
		}

		if (this->cToken->Type() == PWD)
		{
			SyntaxTree* st;
			this->mpop(st);
			Token* opToken = this->cToken;
			this->Advance();
			return new SyntaxTree(opToken, TERM, st, this->Term());
		}

		return nullptr;
	};
	SyntaxTree* Factor()
	{
		SyntaxTree* left = this->Term();
		if(this->LookAhead()==MUL || this->LookAhead()==DIV || this->LookAhead()==RESD)
		{
			this->stack.push(new SyntaxTree(this->cToken, FACT));
			this->Advance();
			return this->Term();
		}
		if (this->cToken->Type() == MUL || this->cToken->Type() == DIV || this->cToken->Type() == RESD )
		{
			SyntaxTree* st;
			this->mpop(st);
			Token* opToken = this->cToken;
			this->Advance();
			return new SyntaxTree(opToken, FACT, st, this->Factor());
		}
		return nullptr;
	};
	SyntaxTree* Expression()
	{
		SyntaxTree* left = this->Term();
		if (this->LookAhead() == MUL || this->LookAhead() == DIV || this->LookAhead() == RESD)
		{
			this->stack.push(new SyntaxTree(this->cToken, FACT));
			this->Advance();
			return this->Term();
		}
		if (this->cToken->Type() == PLUS || this->cToken->Type()==MINUS )
		{
			SyntaxTree* st;
			this->mpop(st);
			Token* opToken = this->cToken;
			this->Advance();
			return new SyntaxTree(opToken, EXP, st, this->Expression());
		}
		return nullptr;
	};
	void Print()
	{
		this->tree->Print();
	};
	SyntaxTree* getSyntaxTree()
	{
		return this->tree;
	};
};

