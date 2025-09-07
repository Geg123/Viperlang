#include"../include/Var.h"
#include<fstream>

struct Interpretator
{
	Interpretator(std::string path);

	Lexer main;
	std::shared_ptr<AST> ast;
	VarCreator var_crt;
	ArrayCreator arr_crt;
	FuncCreator func_crt;


	void runtime();
	void print(std::shared_ptr<NodeAST> node);
};