//
// Created by Иван on 23.02.2023.
//

#include "CriteriaRelation.h"

#include <utility>

CriteriaRelation::CriteriaRelation(Criteria first, CriteriaConstraint constraint, Criteria second) :
        first(first), second(second), constraint(constraint) {}

Criteria CriteriaRelation::getFirstCriteria() {
    return first;
}

Criteria CriteriaRelation::getSecondCriteria() {
    return second;
}

CriteriaConstraint CriteriaRelation::getConstraint() {
    return constraint;
}
