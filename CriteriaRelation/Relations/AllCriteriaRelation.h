#ifndef DMLTESTER_AllCRITERIARELATION_H
#define DMLTESTER_AllCRITERIARELATION_H

#include "../../MathModel/Components/Criteria.h"
#include "../CriteriaRelation.h"

class AllCriteriaRelation : public CriteriaRelation{
private:
    Criteria** criteriaArray;
    int criteriaCount;
    int* idSequence;
public:
    AllCriteriaRelation(Criteria** criteriaArray, int criteriaCount, int* idSequence);
    int getSequenceSize();
    int* getIdSequence();

    bool isValid();
};

#endif //DMLTESTER_AllCRITERIARELATION_H