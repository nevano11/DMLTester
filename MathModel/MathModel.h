#ifndef DMLTESTER_MATHMODEL_H
#define DMLTESTER_MATHMODEL_H

#include "Components/Criteria.h"
#include "Components/EstimateVector.h"

class MathModel {
private:
    Criteria* criteriaArray;
    int criteriaCount;
    EstimateVector* estimateVectorArray;
    int estimateVectorCount;

    int findCriteriaNumById(int criteriaId);
    int findCriteriaNumByName(std::string criteriaName);

public:
    MathModel(Criteria* criteriaArray, int criteriaCount, EstimateVector* estimateVectorArray, int estimateVectorCount);
    Criteria* getCriteriaArray();
    EstimateVector* getEstimateVectorArray();
    int getCriteriaCount();
    int getEstimateVectorCount();

    double sumByCriteria(int criteriaId);
    double sumByCriteria(std::string criteriaName);

    double maxByCriteria(int criteriaId);
    double maxByCriteria(std::string criteriaName);

    double minByCriteria(int criteriaId);
    double minByCriteria(std::string criteriaName);
};

#endif //DMLTESTER_MATHMODEL_H