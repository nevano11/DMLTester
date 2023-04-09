#include "CriteriaRelationConverter.h"

AllCriteriaRelation *CriteriaRelationConverter::convertToAllCriteriaRelation(CriteriaRelation *relation) {
    // if failed return null
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        std::cout << "WeightCriteriaRelation" << std::endl;
        return nullptr;
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        std::cout << "SimpleCriteriaRelation" << std::endl;
        return nullptr;
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        std::cout << "AllCriteriaRelation" << std::endl;
        return (AllCriteriaRelation*) relation;
    }
    return nullptr;
}

SimpleCriteriaRelation *CriteriaRelationConverter::convertToSimpleCriteriaRelation(CriteriaRelation *relation) {
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        std::cout << "WeightCriteriaRelation" << std::endl;
        return nullptr;
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        std::cout << "SimpleCriteriaRelation" << std::endl;
        return (SimpleCriteriaRelation*) relation;
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        std::cout << "AllCriteriaRelation" << std::endl;
        return nullptr;
    }
    return nullptr;
}

WeightCriteriaRelation *CriteriaRelationConverter::convertToWeightCriteriaRelation(CriteriaRelation *relation) {
    if (dynamic_cast<WeightCriteriaRelation*>(relation) != nullptr) {
        std::cout << "WeightCriteriaRelation" << std::endl;
        return (WeightCriteriaRelation*) relation;
    }
    if (dynamic_cast<SimpleCriteriaRelation*>(relation) != nullptr) {
        std::cout << "SimpleCriteriaRelation" << std::endl;
        return nullptr;
    }
    if (dynamic_cast<AllCriteriaRelation*>(relation) != nullptr) {
        std::cout << "AllCriteriaRelation" << std::endl;
        return nullptr;
    }
    return nullptr;
}

CriteriaRelationConverter::CriteriaRelationConverter() {

}
