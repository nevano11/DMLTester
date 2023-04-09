#include "TwoCriteriaRelation.h"

TwoCriteriaRelation::TwoCriteriaRelation(int firstCriteriaId, CriteriaConstraint constraint, int secondCriteriaId) :
        firstId(firstCriteriaId), secondId(secondCriteriaId), constraint(constraint) {
}

TwoCriteriaRelation::TwoCriteriaRelation(const TwoCriteriaRelation& other)
        : firstId(other.firstId), secondId(other.secondId), constraint(other.constraint) {
}

int TwoCriteriaRelation::getFirstCriteriaId() {
    return firstId;
}

int TwoCriteriaRelation::getSecondCriteriaId() {
    return secondId;
}

CriteriaConstraint TwoCriteriaRelation::getConstraint() {
    return constraint;
}

bool TwoCriteriaRelation::isValid() {
    return firstId != secondId;
}

TwoCriteriaRelation *TwoCriteriaRelation::invert() {
    return new TwoCriteriaRelation(secondId, getInvertConstraint(constraint), firstId);
}

bool TwoCriteriaRelation::isRespond(TwoCriteriaRelation *secondRelation) {
    if (firstId == secondRelation->getFirstCriteriaId() && secondId == secondRelation->getSecondCriteriaId())
        return constraint == secondRelation->constraint;
    if (secondId == secondRelation->getFirstCriteriaId() && firstId == secondRelation->getSecondCriteriaId())
        return constraint == getInvertConstraint(secondRelation->constraint);
    return true;
}

CriteriaConstraint TwoCriteriaRelation::getInvertConstraint(CriteriaConstraint constraint) {
    switch (constraint) {
        case CriteriaConstraint::More:
            return CriteriaConstraint::Less;
        case CriteriaConstraint::Less:
            return CriteriaConstraint::More;
        case CriteriaConstraint::MoreOrEquivalent:
            return CriteriaConstraint::LessOrEquivalent;
        case CriteriaConstraint::LessOrEquivalent:
            return CriteriaConstraint::MoreOrEquivalent;
        case CriteriaConstraint::Equivalent:
            return CriteriaConstraint::Equivalent;
    }
}
