#ifndef DMLTESTER_SIMPLECRITERIARELATION_H
#define DMLTESTER_SIMPLECRITERIARELATION_H

#include "../CriteriaRelation.h"
#include "TwoCriteriaRelation.h"

class SimpleCriteriaRelation : public CriteriaRelation{
private:
    Criteria** criteriaArray;
    TwoCriteriaRelation** twoCriteriaRelationArray;
    int criteriaCount;
    int relationCount;
public:
    SimpleCriteriaRelation(Criteria** criteriaArray, TwoCriteriaRelation** twoCriteriaRelationArray, int criteriaCount, int relationCount);
    SimpleCriteriaRelation();

    int getRelationCount();
    TwoCriteriaRelation** getTwoCriteriaRelationArray();

    bool isValid();
};


#endif //DMLTESTER_SIMPLECRITERIARELATION_H
