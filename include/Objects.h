#include"Parser.h"
#include<unordered_map>
#include<unordered_set>
#include<variant>

enum class BasicVarType {BOOL, INT, FLOAT, STRING, CUSTOM};

struct Type;
struct Variable;
struct Array;
struct Function;

using Object = std::variant<std::shared_ptr<Variable>, std::shared_ptr<Array>, std::shared_ptr<Function>, std::nullptr_t>;

//std::shared_ptr<Variable> getPtrToObj(std::shared_ptr<Variable> obj){return obj;}
//std::shared_ptr<Array> getPtrToObj(std::shared_ptr<Array> obj){return obj;}
//std::shared_ptr<Function> getPtrToObj(std::shared_ptr<Function> obj){return obj;}


struct Variable
{
    Variable(std::string _name) : name(_name){}
    Variable(std::string _name, std::string _value) : name(_name), value(_value){}
    Variable(std::string _name, std::string _value, BasicVarType _type) : name(_name), value(_value), type(_type){}
    std::string value;
    BasicVarType type;
    std::string name;
    //bool operator == (Variable* right){return true;}
    //bool operator == (std::shared_ptr<Variable> right){return true;}
};

struct Array
{
    Array(std::string _name) : name(_name){}
    std::vector<Object> array;
    std::string name;
    //bool operator == (Array* right){return true;}
    //bool operator == (std::shared_ptr<Array> right){return true;}
    //std::shared_ptr<Array> operator()(){return std::make_shared<Array>(this);}
};

struct Function
{
    Function(std::string _name) : name(_name){}
    std::unordered_map<size_t, std::string> def_vars;
    std::unordered_map<std::string, Object> objects;
    std::vector<NodeAST> definition_nodes;
    std::string name;
    //bool operator == (Function* right){return true;}
    //bool operator == (std::shared_ptr<Function> right){return true;}
};

BasicVarType VarTypeSelector(std::shared_ptr<NodeAST> node);