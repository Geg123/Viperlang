#include<fstream>

#include"AST.h"


void print(){}
template<typename T, typename... Args>
void print(T First, Args... args)
{
	std::cout << First << " ";
	print(args...);
}

const char* path;

int main()
{
	//std::string line = "if a != b: a = 10;";
	// 	Lexer main(line);
	//main.Analys();
	//main.printTokens();

	std::ifstream file;

	file.open("Text.txt");

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
	}
	else
		std::cout << "File not opened!";
	file.close();
}

int a = 10;


