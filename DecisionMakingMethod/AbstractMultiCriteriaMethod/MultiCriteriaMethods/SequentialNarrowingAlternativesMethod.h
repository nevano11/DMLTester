#ifndef DMLTESTER_SEQUENTIALNARROWINGALTERNATIVESMETHOD_H
#define DMLTESTER_SEQUENTIALNARROWINGALTERNATIVESMETHOD_H

#include "../MultiCriteriaMethod.h"

class SequentialNarrowingAlternativesMethod : public MultiCriteriaMethod {
protected:
    EstimateVector** estimateVectorArray;
    int estimateVectorCount;
public:
    virtual EstimateVector** getEstimateVectorArray() = 0;
    virtual int getEstimateVectorCount() = 0;
};


#endif //DMLTESTER_SEQUENTIALNARROWINGALTERNATIVESMETHOD_H
