#include "IdealDistanceAggregationOperator.h"

#include <climits>
#include <cmath>

std::map<int, double> IdealDistanceAggregationOperator::getEstimateVectorMark(MathModel *mathModel,
                                                                              WeightCriteriaRelation *weightCriteriaRelation) {
    auto criteriaWeightMap = weightCriteriaRelation->getCriteriaWeightMap();
    int estimateVectorCount = mathModel->getEstimateVectorCount();
    auto estimateVectorArray = mathModel->getEstimateVectorArray();

    int criteriaCount = mathModel->getCriteriaCount();

    std::map<int, double> criteriaMaxDistance;

    for (int i = 0; i < criteriaCount; ++i) {
        int criteriaId = mathModel->getCriteriaArray()[i]->getId();
        double max = INT_MIN;
        for (int j = 0; j < estimateVectorCount; ++j) {
            double temp = estimateVectorArray[j]->getMarks()[i] - mathModel->maxByCriteria(criteriaId);
            temp = temp < 0 ? temp * -1 : temp;
            if (max < temp)
                max = temp;
        }
        criteriaMaxDistance.emplace(criteriaId, max);
    }

    for (int i = 0; i < estimateVectorCount; ++i) {
        auto estimateVector = estimateVectorArray[i];
        auto marks = estimateVector->getMarks();
        double res = 0;
        for (int j = 0; j < criteriaCount; ++j) {
            int criteriaId = mathModel->getCriteriaArray()[j]->getId();
            double temp = marks[j] - mathModel->maxByCriteria(criteriaId);
            temp = temp < 0 ? temp * -1 : temp;
            temp = temp / criteriaMaxDistance[criteriaId];
            res += weightCriteriaRelation->getCriteriaWeightMap()[criteriaId] * temp * temp;
        }
        estimateVectorValue.emplace(estimateVector->getId(), pow(res, 0.5));
    }

    return estimateVectorValue;
}

double IdealDistanceAggregationOperator::getBestValue() {
    if (estimateVectorValue.empty())
        return -1;

    double min = INT_MAX;
    for (const auto &item: estimateVectorValue) {
        min = item.second < min ? item.second : min;
    }
    return min;
}

int IdealDistanceAggregationOperator::getBestEstimateVectorId() {
    if (estimateVectorValue.empty())
        return -1;

    double min = INT_MAX;
    int id = INT_MIN;
    for (const auto &item: estimateVectorValue) {
        if (item.second < min) {
            min = item.second;
            id = item.first;
        }
    }
    return id;
}

bool IdealDistanceAggregationOperator::isNeedNormalizedMathModel() {
    return false;
}
