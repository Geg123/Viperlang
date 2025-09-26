#include"Parser.h"

enum class BasicVarType {INT, STRING, BOOL, FLOAT};

struct Variable
{
    Variable(std::string _name) : name(_name){}
    Variable(std::string _name, std::string _value) : name(_name), value(_value){}
    Variable(std::string _name, std::string _value, BasicVarType _type) : name(_name), value(_value), type(_type){}

    std::string name;
    std::string value;
    BasicVarType type;
};

struct Array
{
    Array(std::string _name) : name(_name){}

    std::string name;
    std::vector<std::shared_ptr<Variable>> array;
};

struct Function
{
    Function(std::string _name) : name(_name){}

    std::string name;
    std::vector<std::shared_ptr<NodeAST>> definition_nodes;
};