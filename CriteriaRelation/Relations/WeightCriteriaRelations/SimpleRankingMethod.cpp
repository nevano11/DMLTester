#include "SimpleRankingMethod.h"

SimpleRankingMethod::SimpleRankingMethod() {

}

SimpleRankingMethod::SimpleRankingMethod(Criteria **criteriaArray, int criteriaCount,
                                         std::map<int, double> criteriaIdRankMap) {
    this->criteriaCount = criteriaCount;
    this->criteriaArray = criteriaArray;
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
