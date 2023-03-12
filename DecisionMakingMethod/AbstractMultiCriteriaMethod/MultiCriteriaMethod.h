#ifndef DMLTESTER_MULTICRITERIAMETHOD_H
#define DMLTESTER_MULTICRITERIAMETHOD_H

#include "../DecisionMakingMethod.h"
#include "../../MathModel/MathModel.h"

class MultiCriteriaMethod : public DecisionMakingMethod {
protected:
    MathModel* mathModel;
public:
    virtual void setMathModel(MathModel* mathModel) = 0;
};

#endif //DMLTESTER_MULTICRITERIAMETHOD_H
