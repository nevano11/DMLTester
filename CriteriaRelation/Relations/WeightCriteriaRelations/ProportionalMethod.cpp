#include "ProportionalMethod.h"

ProportionalMethod::ProportionalMethod(int criteriaCount, std::map<int, double> criteriaIdWeightMap) {
    this->criteriaCount = criteriaCount;
    this->criteriaIdWeightMap = criteriaIdWeightMap;
}

bool ProportionalMethod::isValid() {
    return true;
}

std::map<int, double> ProportionalMethod::getCriteriaWeightMap() {
    if (!weightMap.empty())
        return weightMap;

    double sum = 0;
    for (auto & iterator : criteriaIdWeightMap) {
        sum += iterator.second;
    }

    for (auto & iterator : criteriaIdWeightMap) {
        weightMap.emplace(iterator.first, iterator.second / sum);
    }

    return weightMap;
}

CriteriaRelation *ProportionalMethod::copy() {
    return new ProportionalMethod(criteriaCount, criteriaIdWeightMap);
}
