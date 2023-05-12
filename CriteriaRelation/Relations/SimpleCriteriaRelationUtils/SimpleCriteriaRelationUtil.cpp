#include <vector>
#include <algorithm>
#include "SimpleCriteriaRelationUtil.h"

SimpleCriteriaRelationUtil::SimpleCriteriaRelationUtil(SimpleCriteriaRelation *simpleCriteriaRelation) {
    isValid = true;
    this->simpleCriteriaRelation = simpleCriteriaRelation;

    int relationCount = simpleCriteriaRelation->getRelationCount();
    auto relations = simpleCriteriaRelation->getTwoCriteriaRelationArray();
    std::vector<TwoCriteriaRelation*> skippedRelations;
    std::vector<Node*> nodesWithMoreCriteria;

    for (int i = 0; i < relationCount; ++i) {
        auto currentRelation = relations[i]->getConstraint() == CriteriaConstraint::Less ? relations[i]->invert() : relations[i];
        if (currentRelation->getConstraint() == CriteriaConstraint::Equivalent) {
            auto c1 = currentRelation->getFirstCriteriaId();
            auto c2 = currentRelation->getSecondCriteriaId();
            auto iter = std::find_if(nodesWithMoreCriteria.begin(), nodesWithMoreCriteria.end(), [c1, c2](Node *obj) {
                return obj->containsCriteria(c1) || obj->containsCriteria(c2);
            });
            if (iter != nodesWithMoreCriteria.end()) {
                (*iter)->addCriteriaOnNode(c1);
                (*iter)->addCriteriaOnNode(c2);
            } else {
                auto n = new Node(c1);
                n->addCriteriaOnNode(c2);
                nodesWithMoreCriteria.push_back(n);
            }
        }
        else {
            if (currentRelation->getConstraint() == CriteriaConstraint::More) {
                skippedRelations.push_back(currentRelation);
            }
            else {
                isValid = false;
                return;
            }
        }
    }

    for (const auto &currentRelation: skippedRelations) {
        int c1 = currentRelation->getFirstCriteriaId();
        int c2 = currentRelation->getSecondCriteriaId();

        auto iterFirst = std::find_if(nodesWithMoreCriteria.begin(), nodesWithMoreCriteria.end(), [c1](Node *obj) {
            return obj->containsCriteria(c1);
        });
        bool firstFinded = iterFirst != nodesWithMoreCriteria.end();

        auto iterSecond = std::find_if(nodesWithMoreCriteria.begin(), nodesWithMoreCriteria.end(), [c2](Node *obj) {
            return obj->containsCriteria(c2);
        });
        bool secondFinded = iterSecond != nodesWithMoreCriteria.end();

        if (root == nullptr) {
            if (firstFinded) {
                root = (*iterFirst);
                if (secondFinded) {
                    root->addChildNode(*iterSecond);
                } else {
                    auto nn = new Node(c2);
                    nodesWithMoreCriteria.push_back(nn);
                    root->addChildNode(nn);
                }
            } else {
                auto nn = new Node(c1);
                nodesWithMoreCriteria.push_back(nn);
                root = nn;
                if (secondFinded) {
                    root->addChildNode(*iterSecond);
                } else {
                    auto nn2 = new Node(c2);
                    nodesWithMoreCriteria.push_back(nn2);
                    root->addChildNode(nn2);
                }
            }
        }
        else {
            if ((*iterSecond) == root) {
                if (firstFinded) {
                    isValid = false;
                    return;
                }
                auto nn = new Node(c1);
                nodesWithMoreCriteria.push_back(nn);
                root = nn;
                root->addChildNode(*iterSecond);
                continue;
            }

            if (firstFinded && secondFinded) {
                (*iterFirst)->addChildNode(*iterSecond);
            } else if (firstFinded) {
                auto nn = new Node(c2);
                nodesWithMoreCriteria.push_back(nn);
                (*iterFirst)->addChildNode(nn);
            } else if (secondFinded) {
                auto nn = new Node(c1);
                nodesWithMoreCriteria.push_back(nn);
                nn->addChildNode(*iterSecond);
            } else {
                auto nn = new Node(c1);
                auto nn2 = new Node(c2);

                nodesWithMoreCriteria.push_back(nn);
                nodesWithMoreCriteria.push_back(nn2);

                nn->addChildNode(nn2);
            }
        }
    }
}

void SimpleCriteriaRelationUtil::print() {
    if (root == nullptr) {
        std::cout << "Empty tree";
        return;
    }
    root->setDepth(0, simpleCriteriaRelation->getCriteriaCount());
    printNode(0, root);
}

void SimpleCriteriaRelationUtil::printNode(int level, Node *node) {
    for (int i = 0; i < level; ++i) {
        std::cout << "|";
    }
    std::cout << "( ";
    for (const auto &item: node->getCriteriaIdSet()) {
        std::cout << item << " ";
    }
    std::cout << ") " << node->getDepth() << std::endl;
    for (const auto &item: node->getChildNodes()) {
        printNode(level + 1, item);
    }
}

SimpleCriteriaRelationUtil::~SimpleCriteriaRelationUtil() {
    if (root == nullptr)
        return;

    root->deleteChilds();
    delete root;
}

AllCriteriaRelation *SimpleCriteriaRelationUtil::toAllCriteriaRelation() {
    if (!isValid)
        return nullptr;
    int* idSequence = new int[simpleCriteriaRelation->getCriteriaCount()];
    root->setDepth(0, simpleCriteriaRelation->getCriteriaCount());
    return nodeToLexicograficOptimization(idSequence, root) ? new AllCriteriaRelation(simpleCriteriaRelation->getCriteriaCount(), idSequence) : nullptr;
}

bool SimpleCriteriaRelationUtil::nodeToLexicograficOptimization(int* idSequence, Node *node) {
    if (node->getDepth() < 0 || node->getCriteriaIdSet().size() != 1)
        return false;

    idSequence[node->getDepth()] = *node->getCriteriaIdSet().begin();
    for (const auto &childNode: node->getChildNodes()) {
        if (childNode->getDepth() == node->getDepth() + 1)
            return nodeToLexicograficOptimization(idSequence, childNode);
    }

    return true;
}

bool SimpleCriteriaRelationUtil::nodeToWeightOptimization(Node *node, int maxMark, std::map<int, double>& criteriaMarkMap) {
    auto set = node->getCriteriaIdSet();

    if (node->getDepth() < 0 || set.size() < 1)
        return false;

    int sum = 0;
    for (int i = 0; i < set.size(); ++i) {
        sum += maxMark++;
    }
    double avg = sum * 1.0 / set.size();
    for (const auto &criteriaId: set) {
        criteriaMarkMap.emplace(criteriaId, avg);
        criteriaMarkMap.emplace(criteriaId, avg);
    }
    for (const auto &childNode: node->getChildNodes()) {
        if (childNode->getDepth() == node->getDepth() + 1)
            return nodeToWeightOptimization(childNode, maxMark, criteriaMarkMap);
    }

    return true;
}

SimpleRankingMethod *SimpleCriteriaRelationUtil::toWeightCriteriaRelation() {
    if (!isValid)
        return nullptr;
    root->setDepth(0, simpleCriteriaRelation->getCriteriaCount());
    std::map<int, double> criteriaMarkMap;
    return nodeToWeightOptimization(root, 1, criteriaMarkMap) ? new SimpleRankingMethod(simpleCriteriaRelation->getCriteriaCount(), criteriaMarkMap) : nullptr;
}
