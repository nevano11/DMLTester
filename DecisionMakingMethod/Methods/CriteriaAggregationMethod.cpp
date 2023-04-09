#include "CriteriaAggregationMethod.h"

CriteriaAggregationMethod::CriteriaAggregationMethod() {
    this->solveStatus = new SolveStatus(None);
}

CriteriaAggregationMethod::CriteriaAggregationMethod(MathModel *mathModel) {
    this->solveStatus = new SolveStatus(None);
    setMathModel(mathModel);
}

CriteriaAggregationMethod::CriteriaAggregationMethod(MathModel *mathModel, WeightCriteriaRelation *relation) {
    this->solveStatus = new SolveStatus(None);
    setMathModel(mathModel);
    this->relation = relation;
}

void CriteriaAggregationMethod::setMathModel(MathModel *mathModel) {
    this->mathModel = new MathModel(*mathModel);
}

void CriteriaAggregationMethod::setCriteriaRelation(CriteriaRelation *relation) {
    this->relation = CriteriaRelationConverter::convertToWeightCriteriaRelation(relation);
}

void CriteriaAggregationMethod::setAggregationOperator(AggregationOperator *aggregationOperator) {
    this->aggregationOperator = aggregationOperator;
}

void CriteriaAggregationMethod::setNormalizer(Normalizer *normalizer) {
    this->normalizer = normalizer;
}

SolveStatus *CriteriaAggregationMethod::solve() {

    return nullptr;
}
