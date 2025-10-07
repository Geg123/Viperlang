#include"Operators.h"

struct Creator
{
    virtual ~Creator(){}
    Creator(std::shared_ptr<OperatorsManager> _op_manager) : op_manager(_op_manager){}
    virtual void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter){}
protected:
    std::shared_ptr<OperatorsManager> op_manager;
    BasicVarType VarTypeSelector(std::shared_ptr<NodeAST> node);
    void InsertObject(std::shared_ptr<Object> obj);
};

struct ObjectCreator
{
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> objects;
    ObjectCreator(std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> map) : objects(map){}
    void CreateObject(Creator* creator, std::shared_ptr<NodeAST> node, size_t node_iter);
};

struct VarCreator : Creator
{
    VarCreator(std::shared_ptr<OperatorsManager> _op_manager) : Creator(_op_manager){}
    void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter) override;
};
/*struct ArrayCreator : Creator
{
    ArrayCreator(std::shared_ptr<OperatorsManager> _op_manager) : Creator(_op_manager){}
    void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter) override;
};
struct FuncCreator : Creator
{
    FuncCreator(std::shared_ptr<OperatorsManager> _op_manager) : Creator(_op_manager){}
    void CreateObject(std::shared_ptr<NodeAST> node, size_t node_iter) override;
};*/