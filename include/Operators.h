#include"Objects.h"
#include<unordered_map>
#include<unordered_set>

std::unordered_set<TokenType> operators{TokenType::PLUS, TokenType::MINUS, TokenType::MULT, TokenType::DIV, TokenType::MODULE, TokenType::AND, TokenType::OR, TokenType::IS_EQ, TokenType::NOT, TokenType::NOT_EQ};
//for objects.h

struct Operator
{
    virtual ~Operator(){}
    virtual std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST> node);
};

struct Type
{
    ~Type(){}
};

struct OperatorsManager
{
private:
    std::weak_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> objects;
    Operator* _operator;
    Type* type;
public:
    OperatorsManager(std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects);
    Type* TokenTypeToType(std::shared_ptr<NodeAST> node);//is used by DoOperation()
    Operator* NodeTypeToOperator(std::shared_ptr<NodeAST> node);
    void DoOperation(std::shared_ptr<NodeAST> node);
    
};

struct EqOperator : Operator{};
struct PlusOperator : Operator{};
struct MinusOperator : Operator{};
struct MultOperator : Operator{};
struct DivOperator : Operator{};
struct PowerOperator : Operator{};
struct IsEqOperator : Operator{};
struct NotEqOperator : Operator{};
struct NotOperator : Operator{};
struct AndOperator : Operator{};
struct OrOperator : Operator{};
struct GreaterOperator : Operator{};
struct LessOperator : Operator{};
struct SqBracketsOperator : Operator{};

struct NotFullType : Type{};

struct Bool : Type
{
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST>, IsEqOperator* op);
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST>, AndOperator* op);
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST>, OrOperator* op);
    std::shared_ptr<NodeAST> operation(std::shared_ptr<NodeAST>, NotOperator* op);
};
struct Int : Type{};
struct Float : Type{};
struct String : Type{};