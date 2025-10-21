#include"Parser.h"
#include<unordered_map>
#include<unordered_set>
#include<variant>

enum class BasicVarType {BOOL, INT, FLOAT, STRING, CUSTOM};

struct Type;
struct Variable;
struct Array;
struct Function;

using Object = std::variant<std::shared_ptr<Variable>, std::shared_ptr<Array>, std::shared_ptr<Function>>;

struct Variable
{
    Variable(std::string _name) : name(_name){}
    Variable(std::string _name, std::string _value) : name(_name), value(_value){}
    Variable(std::string _name, std::string _value, BasicVarType _type) : name(_name), value(_value), type(_type){}
    std::string value;
    BasicVarType type;
    std::string name;
    bool operator == (Variable* right){return true;}
    bool operator == (std::shared_ptr<Variable> right){return true;}
};

struct Array
{
    Array(std::string _name) : name(_name){}
    std::vector<std::shared_ptr<Object>> array;
    std::string name;
    bool operator == (Array* right){return true;}
    bool operator == (std::shared_ptr<Array> right){return true;}
};

struct Function
{
    Function(std::string _name) : name(_name){}
    std::unordered_set<std::string> def_vars;
    std::unordered_map<std::string, Object> vars;
    std::vector<NodeAST> definition_nodes;
    std::string name;
    bool operator == (Function* right){return true;}
    bool operator == (std::shared_ptr<Function> right){return true;}
};