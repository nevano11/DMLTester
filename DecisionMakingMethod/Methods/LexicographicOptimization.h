#ifndef DMLTESTER_LEXICOGRAPHICOPTIMIZATION_H
#define DMLTESTER_LEXICOGRAPHICOPTIMIZATION_H

#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/OneStepMethod.h"
#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/ProgressingAllAlternativesMethod.h"
#include "../../CriteriaRelation/Relations/AllCriteriaRelation.h"

class LexicographicOptimization : public OneStepMethod, ProgressingAllAlternativesMethod {
private:
    MathModel* mathModel;
    SolveStatus* solveStatus;
    CriteriaRelation* relation;

    void calculateValiditySolveStatus();
public:
    LexicographicOptimization();
    LexicographicOptimization(MathModel *mathModel, CriteriaRelation* relation);
    ~LexicographicOptimization();

    void setMathModel(MathModel* mathModel);
    void setCriteriaRelation(CriteriaRelation* relation);

    SolveStatus* solve();
    MathModel* getMathModel();

    int getBestEstimateVectorId();
};


#endif //DMLTESTER_LEXICOGRAPHICOPTIMIZATION_H
