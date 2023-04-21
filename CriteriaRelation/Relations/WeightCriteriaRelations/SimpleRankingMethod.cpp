#include "SimpleRankingMethod.h"

SimpleRankingMethod::SimpleRankingMethod(int criteriaCount, std::map<int, double> criteriaIdRankMap) {
    this->criteriaCount = criteriaCount;
    this->criteriaIdRankMap = criteriaIdRankMap;
}

bool SimpleRankingMethod::isValid() {
    return true;
}

std::map<int, double> SimpleRankingMethod::getCriteriaWeightMap() {
    if (!weightMap.empty())
        return weightMap;

    int maxRank = criteriaIdRankMap.size() + 1;
    double sum = 0;
    for (auto & iterator : criteriaIdRankMap) {
        sum += iterator.second;
    }

    for (auto & iterator : criteriaIdRankMap) {
        weightMap.emplace(iterator.first, (maxRank - iterator.second) / sum);
    }

    return weightMap;
}

CriteriaRelation *SimpleRankingMethod::copy() {
    return new SimpleRankingMethod(criteriaCount, criteriaIdRankMap);
}
