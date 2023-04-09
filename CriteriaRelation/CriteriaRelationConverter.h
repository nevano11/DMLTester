#ifndef DMLTESTER_CRITERIARELATIONCONVERTER_H
#define DMLTESTER_CRITERIARELATIONCONVERTER_H

#include "Relations/AllCriteriaRelation.h"
#include "Relations/WeightCriteriaRelation.h"
#include "Relations/SimpleCriteriaRelation.h"

class CriteriaRelationConverter {
private:
    CriteriaRelationConverter();
public:
    static AllCriteriaRelation* convertToAllCriteriaRelation(CriteriaRelation* relation);
    static SimpleCriteriaRelation* convertToSimpleCriteriaRelation(CriteriaRelation* relation);
    static WeightCriteriaRelation* convertToWeightCriteriaRelation(CriteriaRelation* relation);
};


#endif //DMLTESTER_CRITERIARELATIONCONVERTER_H
