#include <vector>
#include <algorithm>
#include "CriteriaRelationConverter.h"
#include "Relations/WeightCriteriaRelations/SimpleRankingMethod.h"

AllCriteriaRelation *CriteriaRelationConverter::convertToAllCriteriaRelation(CriteriaRelation *relation) {
    // if failed return null
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        return convertWeightCriteriaRelationToAllCriteriaRelation(dynamic_cast<WeightCriteriaRelation*>(relation));
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        std::cout << "SimpleCriteriaRelation to AllCriteriaRelation" << std::endl;
        return nullptr;
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        return (AllCriteriaRelation*) relation;
    }
    return nullptr;
}

SimpleCriteriaRelation *CriteriaRelationConverter::convertToSimpleCriteriaRelation(CriteriaRelation *relation) {
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        std::cout << "WeightCriteriaRelation to SimpleCriteriaRelation" << std::endl;
        return nullptr;
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        std::cout << "SimpleCriteriaRelation to SimpleCriteriaRelation" << std::endl;
        return (SimpleCriteriaRelation*) relation;
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        std::cout << "AllCriteriaRelation to SimpleCriteriaRelation" << std::endl;
        return nullptr;
    }
    return nullptr;
}

WeightCriteriaRelation *CriteriaRelationConverter::convertToWeightCriteriaRelation(CriteriaRelation *relation) {
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        return (WeightCriteriaRelation*) relation;
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        std::cout << "SimpleCriteriaRelation to WeightCriteriaRelation" << std::endl;
        return nullptr;
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        return convertAllCriteriaRelationToWeightCriteriaRelation((AllCriteriaRelation*) relation);
    }
    return nullptr;
}

CriteriaRelationConverter::CriteriaRelationConverter() {

}

AllCriteriaRelation* CriteriaRelationConverter::convertWeightCriteriaRelationToAllCriteriaRelation(WeightCriteriaRelation *relation) {
    if (relation == nullptr)
        return nullptr;

    auto criteriaWeightMap = relation->getCriteriaWeightMap();
    std::vector<std::pair<int, double>> v(begin(criteriaWeightMap), end(criteriaWeightMap));
    bool hasEqualItems = false;

    std::sort(begin(v), end(v), [&hasEqualItems](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        if (a.second == b.second)
            hasEqualItems = true;
        return a.second > b.second;
    });

    if (hasEqualItems)
        return nullptr;

    int* idSequence = new int[v.size()];
    int i = 0;
    for (const auto &item: v) {
        idSequence[i++] = item.first;
    }
    delete relation;
    return new AllCriteriaRelation(v.size(), idSequence);
}

WeightCriteriaRelation* CriteriaRelationConverter::convertAllCriteriaRelationToWeightCriteriaRelation(AllCriteriaRelation *relation) {
    if (relation == nullptr)
        return nullptr;

    std::map<int, double> criteriaIdRankMap;

    int criteriaCount = relation->getSequenceSize();
    int* idSequence = relation->getIdSequence();
    for (int i = 0; i < criteriaCount; ++i) {
        criteriaIdRankMap.emplace(idSequence[i], i + 1);
    }
    delete relation;
    return new SimpleRankingMethod(relation->getSequenceSize(), criteriaIdRankMap);
}
