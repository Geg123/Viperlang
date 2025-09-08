#include"../include/AST.h"
#include<unordered_map>

//......Var......

enum class VarType;

VarType StringToVarType(std::string str);


struct Variable;
struct VarCreator;
struct Array;
struct ArrayCreator;
struct FuncCreator;
struct Function;

struct Variable;
struct VarCreator;
struct Array;
struct ArrayCreator;
struct FuncCreator;
struct Function;



struct Variable
{
    Variable(std::string _name);
    std::string name;
    VarType type;
    std::string value;
};

struct VarCreator
{
    std::unordered_map<std::string, std::shared_ptr<Variable>> var_list;

    size_t list_iter = 0;

    void CreateVariables(std::shared_ptr<NodeAST> node_eq);
    std::shared_ptr<NodeAST> parseASTNode(std::shared_ptr<NodeAST> node);
    std::shared_ptr<NodeAST> parseASTNode(std::shared_ptr<NodeAST> node, std::shared_ptr<Function> func);
    VarType TypeInit(std::shared_ptr<NodeAST> node);
    std::shared_ptr<ArrayCreator> arr_creator;
    std::shared_ptr<FuncCreator> func_creator;
    Interpretator* my_interpretator;
    //std::shared_ptr<NodeAST> VarCreator::runtime(size_t iter, size_t end_iter, std::shared_ptr<Function> function, bool f);
    ~VarCreator()
    {
        delete my_interpretator;
    }
};

struct Array
{
    Array(std::string _name);
    std::string name;
    std::vector<Variable> array;
};

struct ArrayCreator
{
    size_t list_iter = 0;
    void CreateArray(std::shared_ptr<NodeAST> node_eq);
    Variable setArrIndex(std::shared_ptr<NodeAST> node_index);
    Variable getArrIndex(std::shared_ptr<NodeAST> node_index);
    std::unordered_map<std::string, std::shared_ptr<Array>> list_of_arrays;
    std::shared_ptr<VarCreator> var_crt;
};


struct Function
{
    Function(std::string _name);
    //std::unordered_map<std::string, std::shared_ptr<Variable>> vars;
    std::vector<std::string> vars_names;

    std::string name;
    std::shared_ptr<VarCreator> func_var_crt;
    size_t line_nodes_index = 0;
    size_t last_line_nodes_index = 0;
    //Variable executeFunc(std::shared_ptr<NodeAST> node_first_argue);
};

struct FuncCreator
{
    void CreateFunc(std::shared_ptr<NodeAST> node_func);

    std::unordered_map<std::string, std::shared_ptr<Function>> functions_list;
    std::shared_ptr<VarCreator> var_crt;
};

struct STRUCT
{

};


struct Interpretator
{
    Interpretator(std::string path);
    Interpretator(){}
    


    Lexer main;
    std::shared_ptr<AST> ast;
    VarCreator var_crt;
    ArrayCreator arr_crt;
    FuncCreator func_crt;

    void runtime();
    void runtime(size_t iter, size_t end_iter, std::shared_ptr<Function> function);
    std::shared_ptr<NodeAST> runtime_func(size_t iter, size_t end_iter, std::shared_ptr<Function> function, bool f);
    void print(std::shared_ptr<NodeAST> node);
};