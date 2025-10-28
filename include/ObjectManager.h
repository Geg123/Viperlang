#include"Creator.h"

class ObjectManager
{
public:
    static void InsertObject(Object obj);
    static Object getObject(std::string name);
    static void getValue(std::shared_ptr<NodeAST> node);
    static void setScope(std::string name);
    static void start()
    {
        func_iter = 0;
        setScope("global");
        scope_stack.push("global");
    }
    static void pushScopeStack(std::string name)
    {
        scope_stack.push(name);
    }
    static void popScopeStack()
    {
        scope_stack.pop();
    }
    static std::string getTopScopeStack()
    {
        return scope_stack.top();
    }
    static void incrementIter(){++func_iter;}
    static void decrementIter(){--func_iter;}
    static void CalcExpr(std::shared_ptr<NodeAST> node);
    static void run_func(std::shared_ptr<NodeAST> node, std::shared_ptr<Function> funcptr);
    //standart functions
    static void range(std::shared_ptr<NodeAST> node){}
    static void INT(std::shared_ptr<NodeAST> node){}
    static std::string input();
private:
    ObjectManager();
    static inline size_t func_iter = 0;
    static inline std::stack<std::string> scope_stack;
    static inline std::unordered_map<std::string, Object>* objects;
    static inline std::unordered_map<std::string, Object> global;
    static inline std::unordered_map<std::string, std::unordered_map<std::string, Object>> scopes;
};

NodeAST copyNodeTo(std::shared_ptr<NodeAST> node);
void ToBool(std::shared_ptr<NodeAST> node);