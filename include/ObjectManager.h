#include"Creator.h"

struct ObjectManager
{
public:
    ObjectManager();
    void Create(std::shared_ptr<NodeAST> node, size_t iterator);
    void CalcExpr(std::shared_ptr<NodeAST> node);
    void ExecuteVoidFunc(std::shared_ptr<NodeAST> node);
private:
    void ExecuteFunc(std::shared_ptr<Function> func);
    std::unordered_map<std::string, std::shared_ptr<Object>> objects;
    std::shared_ptr<ObjectCreator> ObjCreator;
};