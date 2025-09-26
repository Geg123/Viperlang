#include"Objects.h"

struct Operator
{
    virtual ~Operator(){}
    virtual std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node) = 0;
};

struct OperatorsManager
{
private:
    Operator* _operator;
public:
    Operator* TokenTypeToOperator(std::shared_ptr<NodeAST> node);//is used by DoOperation()
    void DoOperation(std::shared_ptr<NodeAST> node, Operator* type);
};

struct EqOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct PlusOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct MinusOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct MultOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct DivOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct PowerOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct IsEqOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct NotEqPlusOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct NotPlusOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct AndPlusOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct OrPlusOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct MoreOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct LessOperator : Operator
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};
