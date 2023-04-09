#ifndef DMLTESTER_TWOCRITERIARELATION_H
#define DMLTESTER_TWOCRITERIARELATION_H

#include "../../MathModel/Components/Criteria.h"

enum class CriteriaConstraint { More, Less, MoreOrEquivalent, LessOrEquivalent, Equivalent };

class TwoCriteriaRelation {
private:
    int firstId;
    int secondId;
    CriteriaConstraint constraint;
public:
    TwoCriteriaRelation(int firstCriteriaId, CriteriaConstraint constraint, int secondCriteriaId);
    TwoCriteriaRelation(const TwoCriteriaRelation& other);
    int getFirstCriteriaId();
    int getSecondCriteriaId();
    CriteriaConstraint getConstraint();

    bool isValid();

    TwoCriteriaRelation* invert();
    CriteriaConstraint getInvertConstraint(CriteriaConstraint constraint);
    bool isRespond(TwoCriteriaRelation* secondRelation);
};


#endif //DMLTESTER_TWOCRITERIARELATION_H
