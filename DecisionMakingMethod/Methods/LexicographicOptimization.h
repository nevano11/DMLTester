#ifndef DMLTESTER_LEXICOGRAPHICOPTIMIZATION_H
#define DMLTESTER_LEXICOGRAPHICOPTIMIZATION_H

#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/OneStepMethod.h"
#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/ProgressingAllAlternativesMethod.h"
#include "../../CriteriaRelation/Relations/AllCriteriaRelation.h"

class LexicographicOptimization : public OneStepMethod, ProgressingAllAlternativesMethod {
private:
    MathModel* mathModel;
    SolveStatus* solveStatus;
    AllCriteriaRelation* relation;
public:
    LexicographicOptimization();
    LexicographicOptimization(MathModel *mathModel, AllCriteriaRelation* relation);
    ~LexicographicOptimization();

    void setMathModel(MathModel* mathModel);

    SolveStatus* solve();
    MathModel* getMathModel();
};


#endif //DMLTESTER_LEXICOGRAPHICOPTIMIZATION_H
