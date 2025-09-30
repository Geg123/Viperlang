#include"Operators.h"

struct Creator
{
    virtual ~Creator(){}
    virtual void CreateObject(std::shared_ptr<NodeAST> node) = 0;
};

struct ObjectCreator
{
private:
    OperatorsManager OpManager;
public:
    ObjectCreator(std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> map);
    void CreateObject(Creator* creator);
};

struct VarCreator : Creator
{
    //void CreateObject(std::shared_ptr<NodeAST> node);
};

struct ArrayCreator : Creator
{
    //void CreateObject(std::shared_ptr<NodeAST> node);
};

struct FuncCreator : Creator
{
    //void CreateObject(std::shared_ptr<NodeAST> node);
};

