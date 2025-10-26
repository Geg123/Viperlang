#include"Operators.h"

class Interpretator
{
public:
    Interpretator(std::string path);
private:
    void runtime();
    Lexer main;
    Parser parser;
};