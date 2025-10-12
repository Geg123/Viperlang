#include"Creator.h"

class ObjectManager
{
public:
    ObjectManager();
    void Create(std::shared_ptr<NodeAST> node, size_t iterator, std::shared_ptr<std::vector<std::shared_ptr<NodeAST>>> line_nodes);
    std::shared_ptr<NodeAST> CalcExpr(std::shared_ptr<NodeAST> node);
    bool isObjectFunc(std::string name);
    std::shared_ptr<Function> getFunc(std::string name);
private:
    std::shared_ptr<ObjectCreator> ObjCreator;
    std::unordered_map<std::string, std::shared_ptr<Object>> objects;
};