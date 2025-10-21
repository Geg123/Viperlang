#include"Creator.h"

class Interpretator
{
public:
    Interpretator(std::string path);
private:
    void runtime();
    std::shared_ptr<NodeAST> CalcExpr(std::shared_ptr<NodeAST> node);
    Lexer main;
    Parser parser;
    ObjectManager* objManager;
};