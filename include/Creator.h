#include"Operators.h"
#include<unordered_map>

struct Creator
{
    virtual ~Creator(){}
    virtual void CreateObject(std::shared_ptr<NodeAST> node) = 0;
};

struct ObjectCreator
{
private:
    Creator* creator;
public:
    void CreateObject();
};

struct VarCreator : Creator
{
    void CreateObject(std::shared_ptr<NodeAST> node);
};

struct ArrayCreator : Creator
{
    void CreateObject(std::shared_ptr<NodeAST> node);
};

struct FuncCreator : Creator
{
    void CreateObject(std::shared_ptr<NodeAST> node);
};

