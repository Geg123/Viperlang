#include"ObjectManager.h"

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
        DivOperator, PowerOperator, IsEqOperator, NotOperator, NotEqOperator, AndOperator, 
        OrOperator, GreaterOperator, LessOperator, SqBracketsOperator>;

struct Type
{
    ~Type(){}
    virtual bool test(){return true;}
    virtual void accept(std::shared_ptr<NodeAST> node, Operator* op){}
    virtual void executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op){}
};

struct OperatorsManager
{
private:
    Operator* _operator;
    Type* type;
    ObjectManager* obj_manager = ObjectManager::getInstance();
public:
    TypeOperations NodeTypeToOperator(std::shared_ptr<NodeAST> node);
    Type* TokenTypeToType(std::shared_ptr<NodeAST> node);//is used by DoOperation()
    void DoOperation(std::shared_ptr<NodeAST> node);
};

struct NotFullType : Type
{
    bool test() override {return false;} 
};

struct Bool : Type
{
    void executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op);
private:
    struct Functor
    {
        ObjectManager* obj_manager;
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){obj_manager = ObjectManager::getInstance();}
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
    void executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op);
private:
    struct Functor
    {
        ObjectManager* obj_manager;
        void getVars();
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){obj_manager = ObjectManager::getInstance();}
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
    void executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op);
private:
    struct Functor
    {
        ObjectManager* obj_manager;
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){obj_manager = ObjectManager::getInstance();}
        void operator()(EqOperator& op);
        void operator()(IsEqOperator& op);
        void operator()(AndOperator& op);
        void operator()(OrOperator& op);
        void operator()(NotEqOperator& op);
    };
};
struct String : Type
{
    void executeOperation(std::shared_ptr<NodeAST> node, TypeOperations op);
private:
    struct Functor
    {
        ObjectManager* obj_manager;
        void getVars();
        std::shared_ptr<NodeAST> node;
        Functor(std::shared_ptr<NodeAST> _node) : node(_node){obj_manager = ObjectManager::getInstance();}
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