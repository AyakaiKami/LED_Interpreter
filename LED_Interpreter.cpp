#include <iostream>
#include "Interpreter.h"
Lexer* Lexer::instance = NULL;
Parser* Parser::instance = NULL;
Interpreter* Interpreter::instance = NULL;
int main()
{
    Lexer::getLexer()->MakeTokens("2^2+4-9");
    Lexer::getLexer()->PrintTokens();
    std::vector<Token*>list;
    list = Lexer::getLexer()->SendTokens();
    list[list.size() - 1]->PrintToken();
    std::cout << "\n";
    Parser::getParser()->TokenParser(list);
    Parser::getParser()->Print();
    SyntaxTree* st = Parser::getParser()->getSyntaxTree();
    Interpreter::getInterpreter()->initializer(st);

    std::cout << "\nResult  is : " << Interpreter::getInterpreter()->Choice_TREE(st);
    return 0;
}

