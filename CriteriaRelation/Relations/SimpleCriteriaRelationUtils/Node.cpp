#include "Node.h"

Node::Node() {

}

Node::Node(int criteriaId) {
    criteriaIdSet.emplace(criteriaId);
}

std::set<Node *> Node::getChildNodes() {
    return childNodes;
}

void Node::addCriteriaOnNode(int criteriaId) {
    criteriaIdSet.emplace(criteriaId);
}

void Node::addChildNode(Node *childNode) {
    if (childNode == nullptr)
        return;
    childNodes.emplace(childNode);
}

std::set<int> Node::getCriteriaIdSet() {
    return criteriaIdSet;
}

Node *Node::find(int criteriaId) {
    if (criteriaIdSet.find(criteriaId) != criteriaIdSet.end())
        return this;

    for (const auto &childNode: childNodes) {
        auto findNode = childNode->find(criteriaId);
        if (findNode != nullptr)
            return findNode;
    }
    return nullptr;
}
