#include"Objects.h"
#include<unordered_map>
#include<unordered_set>
#include<variant>
//for objects.h

extern std::unordered_set<TokenType> operators;

struct Operator
{
    virtual ~Operator(){}
};

struct EqOperator : Operator {};
struct PlusOperator : Operator {};
struct MinusOperator : Operator {};
struct MultOperator : Operator {};
struct DivOperator : Operator {};
struct PowerOperator : Operator {};
struct IsEqOperator : Operator {};
struct NotEqOperator : Operator {};
struct NotOperator : Operator {};
struct AndOperator : Operator {};
struct OrOperator : Operator {};
struct GreaterOperator : Operator {};
struct LessOperator : Operator {};
struct SqBracketsOperator : Operator {};

using TypeOperations = std::variant<EqOperator, PlusOperator, MinusOperator, MultOperator,
        DivOperator, PowerOperator,IsEqOperator, NotOperator, NotEqOperator, AndOperator, 
        OrOperator, GreaterOperator, LessOperator, SqBracketsOperator>;

struct Type
{
    ~Type(){}
    virtual bool test(){return true;}
    virtual void accept(std::shared_ptr<NodeAST> node, Operator* op){}
    virtual void executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects){}
};

struct OperatorsManager
{
private:
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> objects;
    Operator* _operator;
    Type* type;
public:
    TypeOperations NodeTypeToOperator(std::shared_ptr<NodeAST> node);
    void InsertObject(std::shared_ptr<Object> obj);
    OperatorsManager(std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects);
    Type* TokenTypeToType(std::shared_ptr<NodeAST> node);//is used by DoOperation()
    void DoOperation(std::shared_ptr<NodeAST> node);

};

struct NotFullType : Type
{
    bool test() override {return false;} 
};

struct Bool : Type
{
    void executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects);
private:
    struct Functor
    {
        std::shared_ptr<NodeAST> node;
        std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> objects;
        Functor(std::shared_ptr<NodeAST> _node, std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<Object>>> _objects) : node(_node), objects(_objects){}
        void operator()(EqOperator& op);
        void operator()(IsEqOperator& op);
        void operator()(AndOperator& op);
        void operator()(OrOperator& op);
        void operator()(NotEqOperator& op);
    };
};
struct Int : Type{};
struct Float : Type{};
struct String : Type{};