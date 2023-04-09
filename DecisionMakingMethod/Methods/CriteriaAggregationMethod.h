#ifndef DMLTESTER_CRITERIAAGGREGATIONMETHOD_H
#define DMLTESTER_CRITERIAAGGREGATIONMETHOD_H

#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/OneStepMethod.h"
#include "../AbstractMultiCriteriaMethod/MultiCriteriaMethods/ProgressingAllAlternativesMethod.h"
#include "../../CriteriaRelation/Relations/WeightCriteriaRelation.h"
#include "AuxiliaryMethods/AggregationOperator.h"
#include "../../MathModel/Converters/Normalizer.h"

class CriteriaAggregationMethod : public OneStepMethod, ProgressingAllAlternativesMethod{
private:
    MathModel* mathModel;
    SolveStatus* solveStatus;
    CriteriaRelation* relation;
    AggregationOperator* aggregationOperator;
    Normalizer* normalizer;
public:
    CriteriaAggregationMethod();
    CriteriaAggregationMethod(MathModel* mathModel);
    CriteriaAggregationMethod(MathModel* mathModel, WeightCriteriaRelation* relation);

    void setMathModel(MathModel* mathModel);
    void setCriteriaRelation(CriteriaRelation* relation);
    void setAggregationOperator(AggregationOperator* aggregationOperator);
    void setNormalizer(Normalizer* normalizer);

    SolveStatus* solve();
};


#endif //DMLTESTER_CRITERIAAGGREGATIONMETHOD_H
