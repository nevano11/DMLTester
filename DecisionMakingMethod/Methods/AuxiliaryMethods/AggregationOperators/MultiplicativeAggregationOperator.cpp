#include "MultiplicativeAggregationOperator.h"

#include <climits>
#include <cmath>

std::map<int, double> MultiplicativeAggregationOperator::getEstimateVectorMark(MathModel *normalizedMathModel,
                                                                          WeightCriteriaRelation *weightCriteriaRelation) {
    auto criteriaWeightMap = weightCriteriaRelation->getCriteriaWeightMap();
    int estimateVectorCount = normalizedMathModel->getEstimateVectorCount();
    auto estimateVectorArray = normalizedMathModel->getEstimateVectorArray();

    int criteriaCount = normalizedMathModel->getCriteriaCount();

    for (int i = 0; i < estimateVectorCount; ++i) {
        auto estimateVector = estimateVectorArray[i];
        auto marks = estimateVector->getMarks();
        double res = 0;
        for (int j = 0; j < criteriaCount; ++j) {
            int criteriaId = normalizedMathModel->getCriteriaArray()[j]->getId();
            res *= pow(marks[j], weightCriteriaRelation->getCriteriaWeightMap()[criteriaId]);
        }
        estimateVectorValue.emplace(estimateVector->getId(), res);
    }

    return estimateVectorValue;
}

double MultiplicativeAggregationOperator::getBestValue() {
    if (!estimateVectorValue.empty())
        return -1;

    double max = INT_MIN;
    for (const auto &item: estimateVectorValue) {
        max = item.second > max ? item.second : max;
    }
    return max;
}

int MultiplicativeAggregationOperator::getBestEstimateVectorId() {
    if (!estimateVectorValue.empty())
        return -1;

    double max = INT_MIN;
    int id = INT_MIN;
    for (const auto &item: estimateVectorValue) {
        if (item.second > max) {
            max = item.second > max;
            id = item.first;
        }
    }
    return id;
}