#include "Token.h"
#include <vector>

class Lexer
{
private:
	std::vector<Token*> List_Tokens;
	std::string text;
	int index_text = 0;
	static Lexer* instance;
	Lexer() = default;
	~Lexer() = default;
public:
	Lexer(const Lexer& obj) = delete;
	static Lexer* getLexer()
	{
		if (instance == NULL)
		{
			instance = new Lexer();
		}
		return instance;
	};
	void Advance() { this->index_text++; };
	void MakeTokens(std::string line_text)
	{
		this->text = line_text;
		while (text[index_text] != '\n' && text[index_text] != '\0')
		{
			while (text[index_text] == ' ' || text[index_text] == '\t')
			{
				this->Advance();
			}
			switch (text[index_text])
			{
			case '+':List_Tokens.push_back(new Token(PLUS)); this->Advance(); break;
			case '-':List_Tokens.push_back(new Token(MINUS)); this->Advance(); break;
			case '=':List_Tokens.push_back(new Token(EQ)); this->Advance(); break;
			case '/':List_Tokens.push_back(new Token(DIV)); this->Advance(); break;
			case '%':List_Tokens.push_back(new Token(RESD)); this->Advance(); break;
			case '*':List_Tokens.push_back(new Token(MUL)); this->Advance(); break;
			case '^':List_Tokens.push_back(new Token(PWD)); this->Advance(); break;
			case '(':List_Tokens.push_back(new Token(LPAR)); this->Advance(); break;
			case ')':List_Tokens.push_back(new Token(RPAR)); this->Advance(); break;
			default:
				if ((text[index_text] >= 'a' && text[index_text] <= 'z') ||
					(text[index_text] >= 'A' && text[index_text] <= 'Z') || text[index_text] == '_')
					List_Tokens.push_back(MakeWord());
				else
					if (text[index_text] >= '0' && text[index_text] <= '9')
						List_Tokens.push_back(MakeInteger());
					else
						throw("Unknown characher\n");
				break;
			}
		}
	};
	Token* MakeInteger()
	{
		std::string value;
		while (text[index_text] >= '0' && text[index_text] <= '9')
		{
			value += text[index_text];
			this->Advance();
		}
		return new Token(Integer, value);
	}
	Token* MakeWord()
	{
		std::string value;
		while ((text[index_text] >= '0' && text[index_text] <= '9') ||
			(text[index_text] >= 'a' && text[index_text] <= 'z') ||
			(text[index_text] >= 'A' && text[index_text] <= 'Z') || text[index_text] == '_'
			)
		{
			value += text[index_text];
			this->Advance();
		}
		return new Token(Identifier, value);
	};
	void PrintTokens()
	{
		int nr = 0;
		std::vector<Token*>::iterator i;
		for (i = List_Tokens.begin(); i != List_Tokens.end(); i++)
		{
			std::cout << nr++ << " ";
			(*i)->PrintToken();
			std::cout << " , ";
		}
		std::cout << "\n";
	};
	std::vector<Token*> SendTokens()
	{
		return this->List_Tokens;
	};
};

