#ifndef DMLTESTER_CRITERIARELATION_H
#define DMLTESTER_CRITERIARELATION_H

#include "../MathModel/Components/Criteria.h"

class CriteriaRelation {
protected:
    Criteria** criteriaArray;
    int criteriaCount;
public:
    virtual bool isValid() = 0;
};

#endif //DMLTESTER_CRITERIARELATION_H
