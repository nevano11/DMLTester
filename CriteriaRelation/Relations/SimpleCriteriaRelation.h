#ifndef DMLTESTER_SIMPLECRITERIARELATION_H
#define DMLTESTER_SIMPLECRITERIARELATION_H

#include "../CriteriaRelation.h"
#include "TwoCriteriaRelation.h"

class SimpleCriteriaRelation : public CriteriaRelation{
private:
    Criteria** criteriaArray;
    TwoCriteriaRelation** twoCriteriaRelationArray;
public:
    SimpleCriteriaRelation(Criteria** criteriaArray, TwoCriteriaRelation** twoCriteriaRelationArray);

    virtual AllCriteriaRelation* convertToAllCriteriaRelation() = 0;
    virtual SimpleCriteriaRelation* convertToSimpleCriteriaRelation() = 0;
    virtual WeightCriteriaRelation* convertToWeightCriteriaRelation() = 0;

    virtual bool isValid() = 0;
};


#endif //DMLTESTER_SIMPLECRITERIARELATION_H
