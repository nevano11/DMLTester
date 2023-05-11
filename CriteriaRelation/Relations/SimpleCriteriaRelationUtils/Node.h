#ifndef DMLTESTER_NODE_H
#define DMLTESTER_NODE_H

#include <set>

class Node {
private:
    std::set<int> criteriaIdSet;
    int depth;
    std::set<Node*> childNodes;
public:
    Node();
    Node(int criteriaId);

    void addCriteriaOnNode(int criteriaId);
    void addChildNode(Node* childNode);

    std::set<Node*> getChildNodes();
    std::set<int> getCriteriaIdSet();

    Node *find(int criteriaId);
};


#endif //DMLTESTER_NODE_H
