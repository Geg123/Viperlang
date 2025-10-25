#include"Operators.h"

class Creator
{
public:
    virtual ~Creator(){}
    virtual void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes){}
protected:
    std::shared_ptr<OperatorsManager> op_manager;
    BasicVarType VarTypeSelector(std::shared_ptr<NodeAST> node);
};

void CreateObject(Creator* creator, std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes);

class VarCreator : Creator
{
public:
    void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes) override;
};
class ArrayCreator : Creator
{
public:
    void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes) override{}
};
class FuncCreator : Creator
{
public:
    void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes) override;
};