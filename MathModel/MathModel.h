#ifndef DMLTESTER_MATHMODEL_H
#define DMLTESTER_MATHMODEL_H

#include "Components/Criteria.h"
#include "Components/EstimateVector.h"

class MathModel {
private:
    Criteria** criteriaArray;
    int criteriaCount;
    EstimateVector** estimateVectorArray;
    int estimateVectorCount;

    bool isDoubleEqual(double a, double b);

public:
    MathModel(Criteria **criteriaArray, int criteriaCount, EstimateVector **estimateVectorArray, int estimateVectorCount);
    MathModel(const MathModel& other);
    ~MathModel();
    
    Criteria** getCriteriaArray();
    EstimateVector** getEstimateVectorArray();
    int getCriteriaCount();
    int getEstimateVectorCount();

    Criteria* getCriteriaById(int id);
    Criteria* getCriteriaByName(std::string name);

    int findCriteriaNumById(int criteriaId);
    int findCriteriaNumByName(std::string criteriaName);

    double sumByCriteria(int criteriaId);
    double sumByCriteria(std::string criteriaName);

    double maxByCriteria(int criteriaId);
    double maxByCriteria(std::string criteriaName);

    double minByCriteria(int criteriaId);
    double minByCriteria(std::string criteriaName);

    void deleteEstimateVectorIfMarkNotEqualValue(int criteriaNum, double value);

    bool isValid();

    std::string estimateVectorArrayToString();
};

#endif //DMLTESTER_MATHMODEL_H