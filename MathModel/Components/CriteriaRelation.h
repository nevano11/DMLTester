#ifndef DMLTESTER_CRITERIARELATION_H
#define DMLTESTER_CRITERIARELATION_H

#include "Criteria.h"

enum CriteriaConstraint { More, Less, MoreOrEquivalent, LessOrEquivalent, Equivalent };

class CriteriaRelation {
private:
    Criteria first;
    Criteria second;
    CriteriaConstraint constraint;
public:
    CriteriaRelation(Criteria first, CriteriaConstraint constraint, Criteria second);
    Criteria getFirstCriteria();
    Criteria getSecondCriteria();
    CriteriaConstraint getConstraint();
};


#endif //DMLTESTER_CRITERIARELATION_H
