#include"../include/AST.h"
#include<unordered_map>

//......Var......

enum class VarType;

VarType StringToVarType(std::string str);

struct Array;
struct ArrayCreator;
struct FuncCreator;


struct Variable
{
    Variable(std::string _name);
    std::string name;
    VarType type;
    std::string value;
};

struct VarCreator
{
    std::unordered_map<std::string,std::shared_ptr<Variable>> var_list;

    size_t list_iter = 0;

    void CreateVariables(std::shared_ptr<NodeAST> node_eq);
    std::shared_ptr<NodeAST> parseASTNode(std::shared_ptr<NodeAST> node);
    VarType TypeInit(std::shared_ptr<NodeAST> node);
    std::shared_ptr<ArrayCreator> arr_creator;
    std::shared_ptr<FuncCreator> func_crator;
   
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
    std::shared_ptr<VarCreator> var_creator;
};


struct Function
{
    Function(std::string  _name);
    std::vector<Variable> vars;
    std::string name;
    size_t quatity_of_var;
    Variable executeFunc(std::shared_ptr<NodeAST> node_first_argue);
};

struct FuncCreator
{

    void CreateFunc(std::shared_ptr<NodeAST> node_colon);

    std::unordered_map<std::string,std::shared_ptr<Function>> functions_list;
    std::shared_ptr<VarCreator> var_crt;
};

struct STRUCT
{

};