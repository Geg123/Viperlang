#include"Creator.h"

struct Interpretator
{
    Interpretator(std::string path);
    Interpretator(){}
    void runtime();
    void runtime(size_t iter, size_t end_iter);
    std::shared_ptr<NodeAST> runtime_func(size_t iter, size_t end_iter, std::shared_ptr<Function> function, bool f);
    void print(std::shared_ptr<NodeAST> node);

    Lexer main;
    Parser parser;
    ObjectCreator creator;
};