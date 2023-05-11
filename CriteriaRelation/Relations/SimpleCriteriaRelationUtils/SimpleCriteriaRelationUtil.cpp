#include <vector>
#include "SimpleCriteriaRelationUtil.h"

SimpleCriteriaRelationUtil::SimpleCriteriaRelationUtil(SimpleCriteriaRelation *simpleCriteriaRelation) {
    isValid = true;

    int relationCount = simpleCriteriaRelation->getRelationCount();
    int criteriaCount = simpleCriteriaRelation->getCriteriaCount();
    auto relations = simpleCriteriaRelation->getTwoCriteriaRelationArray();
    std::vector<TwoCriteriaRelation*> skippedRelations;

    for (int i = 0; i < relationCount; ++i) {
        auto currentRelation = relations[i]->getConstraint() == CriteriaConstraint::Less ? relations[i]->invert() : relations[i];

        if (root == nullptr) {
            root = new Node(currentRelation->getFirstCriteriaId());
            if (currentRelation->getConstraint() == CriteriaConstraint::Equivalent)
                root->addCriteriaOnNode(currentRelation->getSecondCriteriaId());
            else if (currentRelation->getConstraint() == CriteriaConstraint::More)
                root->addChildNode(new Node(currentRelation->getSecondCriteriaId()));
            else {
                isValid = false;
                return;
            }
            continue;
        }

        Node* node = root->find(currentRelation->getFirstCriteriaId());
        if (node == nullptr) {
            node = root->find(currentRelation->getSecondCriteriaId());
            if (node == nullptr) {
                skippedRelations.push_back(currentRelation);
                continue;
            }

        }
        if (currentRelation->getConstraint() == CriteriaConstraint::Equivalent)
            node->addCriteriaOnNode(currentRelation->getSecondCriteriaId());
        else if (currentRelation->getConstraint() == CriteriaConstraint::More)
            node->addChildNode(new Node(currentRelation->getSecondCriteriaId()));
        else {
            isValid = false;
            return;
        }
    }
}


