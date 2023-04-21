#include "AllCriteriaRelation.h"

AllCriteriaRelation::AllCriteriaRelation(int criteriaCount, int* idSequence)
{
    this->criteriaCount = criteriaCount;
    this->idSequence = new int[criteriaCount];
    
    for (size_t i = 0; i < criteriaCount; i++)
    {
        this->idSequence[i] = idSequence[i];
    }
}

int AllCriteriaRelation::getSequenceSize()
{
    return criteriaCount;
}

int *AllCriteriaRelation::getIdSequence()
{
    return idSequence;
}

bool AllCriteriaRelation::isValid()
{
    if (criteriaCount < 1 || idSequence == nullptr)
        return false;

    // Check is criteria id unique
    for(int i = 0; i < criteriaCount - 1; i++)
        for(int j = i + 1; j < criteriaCount; j++) 
            if(idSequence[i] == idSequence[j])
                return false;

    return true;
}

CriteriaRelation *AllCriteriaRelation::copy() {
    return new AllCriteriaRelation(criteriaCount, getIdSequence());;
}
