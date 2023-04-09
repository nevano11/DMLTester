#include "AllCriteriaRelation.h"

AllCriteriaRelation::AllCriteriaRelation(Criteria** criteriaArray, int criteriaCount, int* idSequence)
{
    this->criteriaArray = criteriaArray;
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
    if (criteriaCount < 1 || criteriaArray == nullptr)
        return false;

    for (size_t i = 0; i < criteriaCount; i++)
        if (criteriaArray[i] == nullptr)
            return false;

    // Check is criteria id unique
    for(int i = 0; i < criteriaCount - 1; i++)
        for(int j = i + 1; j < criteriaCount; j++) 
            if(criteriaArray[i]->getId() == criteriaArray[j]->getId()) 
                return false;

    // Сheck the matching of arrays (criteriaArray)
    int commonElementsCount = 0;
    for (size_t i = 0; i < criteriaCount; i++)
    {
        int element = criteriaArray[i]->getId();
        for (size_t i = 0; i < criteriaCount; i++)
            if (idSequence[i] == element) {
                commonElementsCount++;
                break;
            }
    }
    return commonElementsCount == criteriaCount;
}