#include"ObjectManager.h"

extern std::unordered_set<TokenType> operators;

struct EqOperator{};
struct PlusOperator{};
struct MinusOperator{};
struct MultOperator{};
struct DivOperator{};
struct PowerOperator{};
struct IsEqOperator{};
struct NotEqOperator{};
struct NotOperator{};
struct AndOperator{};
struct OrOperator{};
struct GreaterOperator{};
struct LessOperator{};
struct SqBracketsOperator{};

using Operator = std::variant<EqOperator, PlusOperator, MinusOperator, MultOperator,
        DivOperator, PowerOperator, IsEqOperator, NotOperator, NotEqOperator, AndOperator, 
        OrOperator, GreaterOperator, LessOperator, SqBracketsOperator>;

struct Type
{
    ~Type(){}
    virtual bool test(){return true;}
    virtual void accept(std::shared_ptr<NodeAST> node, Operator* op){}
    virtual void executeOperation(std::shared_ptr<NodeAST> node, Operator op){}
};

struct OperatorsManager
{
private:
    Operator* _operator;
    Type* type;
public:
    Operator NodeTypeToOperator(std::shared_ptr<NodeAST> node);
    Type* TokenTypeToType(std::shared_ptr<NodeAST> node);//is used by DoOperation()
    void DoOperation(std::shared_ptr<NodeAST> node);
};

struct NotFullType : Type
{
    bool test() override {return false;} 
};

struct Bool : Type
{
    void executeOperation(std::shared_ptr<NodeAST> node, Operator op);
private:
    struct Functor
    {        
        void getObjects();
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){}
        void operator()(EqOperator& op);
        void operator()(IsEqOperator& op);
        void operator()(AndOperator& op);
        void operator()(OrOperator& op);
        void operator()(NotEqOperator& op);
        void operator()(SqBracketsOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(NotOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(MultOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(PlusOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(MinusOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(DivOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(PowerOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(LessOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(GreaterOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
    };
};
struct Int : Type
{
    void executeOperation(std::shared_ptr<NodeAST> node, Operator op);
private:
    struct Functor
    {        
        void getObjects();
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){}
        void operator()(EqOperator& op);
        void operator()(PlusOperator& op);
        void operator()(MinusOperator& op);
        void operator()(MultOperator& op);
        void operator()(DivOperator& op);
        void operator()(PowerOperator& op);
        void operator()(GreaterOperator& op);
        void operator()(LessOperator& op);
        void operator()(IsEqOperator& op);
        void operator()(NotEqOperator& op);
        void operator()(SqBracketsOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(NotOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(AndOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(OrOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
    };
};
struct Float : Type
{
    void executeOperation(std::shared_ptr<NodeAST> node, Operator op);
private:
    struct Functor
    {
        void getObjects();
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){}
        void operator()(EqOperator& op);
        void operator()(IsEqOperator& op);
        void operator()(AndOperator& op);
        void operator()(OrOperator& op);
        void operator()(NotEqOperator& op);
    };
};
struct String : Type
{
    void executeOperation(std::shared_ptr<NodeAST> node, Operator op);
private:
    struct Functor
    {
        void getObjects();
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){}
        void operator()(EqOperator& op);
        void operator()(IsEqOperator& op);
        void operator()(NotEqOperator& op);
        void operator()(PlusOperator& op);
        void operator()(MultOperator& op);
        void operator()(SqBracketsOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(NotOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(AndOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(OrOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(MinusOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(DivOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(PowerOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(LessOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
        void operator()(GreaterOperator& op){std::cerr << "Error: you can't do this operation!\n"; system("pause");}
    };
};