#include"Operators.h"

/*class Creator
{
public:
    virtual ~Creator(){}
    virtual void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes){}
protected:
    std::shared_ptr<OperatorsManager> op_manager;
    BasicVarType VarTypeSelector(std::shared_ptr<NodeAST> node);
};*/


class VarCreator
{
public:
    void CreateObject(std::shared_ptr<NodeAST> node);
};
class ArrayCreator
{
public:
    void CreateObject(std::shared_ptr<NodeAST> node);
};
class FuncCreator
{
public:
    void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter);
};