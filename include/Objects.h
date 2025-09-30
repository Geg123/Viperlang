#include"Parser.h"
#include<unordered_map>

enum class BasicVarType {INT, STRING, BOOL, FLOAT};

struct Type;

struct Object
{
    virtual ~Object(){}
    virtual void Create(std::shared_ptr<NodeAST> node);
    Object(std::string _name) : name(_name){}

    std::string name;
};

struct Variable : Object
{
    Variable(std::string _name) : Object(_name){}
    Variable(std::string _name, std::string _value) : Object(_name), value(_value){}
    Variable(std::string _name, std::string _value, BasicVarType _type) : Object(_name), value(_value), type(_type){}
    void Create(std::shared_ptr<NodeAST> node);
    std::string value;
    BasicVarType type;
};

struct Array : Object
{
    Array(std::string _name) : Object(_name){}
    void Create(std::shared_ptr<NodeAST> node);

    std::vector<std::shared_ptr<Variable>> array;
};

struct Function : Object
{
    Function(std::string _name) : Object(_name){}
    void Create(std::shared_ptr<NodeAST> node);

    std::vector<std::shared_ptr<NodeAST>> definition_nodes;
};

struct ObjectManager
{
    void Create(std::shared_ptr<NodeAST> node, Object* obj_type);
    void ExecuteVoidFunc(std::shared_ptr<NodeAST> node);

    ObjectCreator ObjCreator;
    std::unordered_map<std::string, std::shared_ptr<Object>> objects;
};