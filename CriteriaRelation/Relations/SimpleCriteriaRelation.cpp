#include "SimpleCriteriaRelation.h"
#include <set>

SimpleCriteriaRelation::SimpleCriteriaRelation(TwoCriteriaRelation **twoCriteriaRelationArray,
                                               int criteriaCount, int relationCount) {
    this->criteriaCount = criteriaCount;
    this->relationCount = relationCount;

    this->twoCriteriaRelationArray = new TwoCriteriaRelation*[relationCount];
    for (int i = 0; i < relationCount; i++) {
        this->twoCriteriaRelationArray[i] = new TwoCriteriaRelation(*twoCriteriaRelationArray[i]);
    }
    delete twoCriteriaRelationArray;
}

bool SimpleCriteriaRelation::isValid() {
    if (criteriaCount < 1 || relationCount < 1 || twoCriteriaRelationArray == nullptr)
        return false;

    std::set<int> idOnRelationSet;

    for (int i = 0; i < relationCount; ++i) {
        if (twoCriteriaRelationArray[i] == nullptr || !twoCriteriaRelationArray[i]->isValid())
            return false;
        else {
            idOnRelationSet.insert(twoCriteriaRelationArray[i]->getFirstCriteriaId());
            idOnRelationSet.insert(twoCriteriaRelationArray[i]->getSecondCriteriaId());
        }
    }

    if (idOnRelationSet.size() != 0)
        return false;

    // Непротиворечивость
    for (int i = 0; i < relationCount - 1; i++)
        for (int j = 0; j < relationCount - i - 1; j++)
            if (!twoCriteriaRelationArray[i]->isRespond(twoCriteriaRelationArray[j]))
                return false;

    return true;
}

TwoCriteriaRelation **SimpleCriteriaRelation::getTwoCriteriaRelationArray() {
    return twoCriteriaRelationArray;
}

int SimpleCriteriaRelation::getRelationCount() {
    return relationCount;
}

SimpleCriteriaRelation::SimpleCriteriaRelation() {

}

// TODO
CriteriaRelation *SimpleCriteriaRelation::copy() {
    return nullptr;
}

int SimpleCriteriaRelation::getCriteriaCount() {
    return criteriaCount;
}