#include "MinMaxNormalizer.h"
#include <map>

MathModel *MinMaxNormalizer::getNormalizedMathModel(MathModel *original) {
    if (!original->isValid())
        return nullptr;

    std::map<int, double> criteriaDeltaMaxMin;
    std::map<int, double> criteriaMin;

    Criteria** criteriaArray = original->getCriteriaArray();
    int criteriaCount = original->getCriteriaCount();

    for (int i = 0; i < criteriaCount; ++i) {
        int id = criteriaArray[i]->getId();
        int max = original->maxByCriteria(id);
        int min = original->minByCriteria(id);

        criteriaDeltaMaxMin.emplace(i, max - min);
        criteriaMin.emplace(i, min);
    }

    EstimateVector** estimateVectorArray = original->getEstimateVectorArray();
    int estimateVectorCount = original->getEstimateVectorCount();

    EstimateVector** normalizedEstimateVectorArray = new EstimateVector*[estimateVectorCount];

    for (int i = 0; i < estimateVectorCount; ++i) {
        double* normalizedMarks = new double[criteriaCount];
        double* oldMarks = estimateVectorArray[i]->getMarks();

        for (int j = 0; j < criteriaCount; ++j) {
            normalizedMarks[j] = (oldMarks[j] - criteriaMin[j]) / criteriaDeltaMaxMin[j];
        }

        normalizedEstimateVectorArray[i] = new EstimateVector(
                estimateVectorArray[i]->getId(),
                estimateVectorArray[i]->getName(),
                normalizedMarks,
                criteriaCount);
    }

    return new MathModel(criteriaArray, criteriaCount,normalizedEstimateVectorArray, estimateVectorCount);
}
