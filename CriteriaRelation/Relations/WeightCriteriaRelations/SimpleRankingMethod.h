#ifndef DMLTESTER_SIMPLERANKINGMETHOD_H
#define DMLTESTER_SIMPLERANKINGMETHOD_H

#include "../WeightCriteriaRelation.h"
#include <map>

// TODO isValid Method
class SimpleRankingMethod : public WeightCriteriaRelation {
private:
    std::map<int, double> weightMap;
protected:
    std::map<int, double> criteriaIdRankMap;
    Criteria** criteriaArray;
    int criteriaCount;
public:
    SimpleRankingMethod();
    SimpleRankingMethod(Criteria** criteriaArray, int criteriaCount, std::map<int, double> criteriaIdRankMap);

    std::map<int, double> getCriteriaWeightMap();

    bool isValid();
};


#endif //DMLTESTER_SIMPLERANKINGMETHOD_H
