#ifndef DMLTESTER_PROPORTIONALMETHOD_H
#define DMLTESTER_PROPORTIONALMETHOD_H

#include "../WeightCriteriaRelation.h"
#include <map>

class ProportionalMethod : public WeightCriteriaRelation{
private:
    std::map<int, double> weightMap;
protected:
    std::map<int, double> criteriaIdWeightMap;
    Criteria** criteriaArray;
    int criteriaCount;
public:
    ProportionalMethod();
    ProportionalMethod(Criteria **criteriaArray, int criteriaCount, std::map<int, double> criteriaIdWeightMap);

    std::map<int, double> getCriteriaWeightMap();
    bool isValid();
};


#endif //DMLTESTER_PROPORTIONALMETHOD_H
