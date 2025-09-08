

#include"../include/Var.h"


int main()
{
	Interpretator main("C:/func_test.txt");
}









/*void print() {}
template<typename T, typename... Args>
void print(T First, Args... args)
{
	std::cout << First << " ";
	print(args...);
}*/


//std::string line = "if a != b: a = 10;";
	// 	Lexer main(line);
	//main.Analys();
	//main.printTokens();

//int a = 10;

/*void f()
{
	std::ifstream file;

	file.open("C:/Text.txt");

	if (file.is_open()) {
		std::string in;

		Lexer main;

		while (std::getline(file, in))
		{
			main.line = in;
			main.Analys();
		}
		main.printTokens();

		AST ast(&main);
		ast.Analys();
		std::cout << TokenTypeSwitch(ast.line_nodes[0]->left->token->type) << " " << ast.line_nodes[0]->left->token->value << "\n";
		std::cout << TokenTypeSwitch(ast.line_nodes[0]->token->type) << " " << ast.line_nodes[0]->token->value << "\n";
		std::cout << TokenTypeSwitch(ast.line_nodes[0]->right->token->type) << " " << ast.line_nodes[0]->right->token->value << "\n";
		std::cout << TokenTypeSwitch(ast.line_nodes[1]->token->type) << " " << ast.line_nodes[1]->token->value << "\n";
		std::cout << TokenTypeSwitch(ast.line_nodes[1]->right->token->type) << " " << ast.line_nodes[1]->right->token->value << "\n";

	}
	else
		std::cout << "File not opened!";
	file.close();
	system("pause");
}

*/

