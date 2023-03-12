#ifndef DMLTESTER_CRITERIARELATION_H
#define DMLTESTER_CRITERIARELATION_H

#include "Relations/SimpleCriteriaRelation.h"
#include "Relations/WeightCriteriaRelation.h"
#include "Relations/AllCriteriaRelation.h"

class CriteriaRelation {
protected:
    Criteria** criteriaArray;
public:
    virtual AllCriteriaRelation* convertToAllCriteriaRelation() = 0;
    virtual SimpleCriteriaRelation* convertToSimpleCriteriaRelation() = 0;
    virtual WeightCriteriaRelation* convertToWeightCriteriaRelation() = 0;

    virtual bool isValid() = 0;
};

#endif //DMLTESTER_CRITERIARELATION_H
