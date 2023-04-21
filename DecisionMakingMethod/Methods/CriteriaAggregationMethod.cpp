#include "CriteriaAggregationMethod.h"
#include "../../MathModel/Converters/Normalizers/MinMaxNormalizer.h"

CriteriaAggregationMethod::CriteriaAggregationMethod(AggregationOperator* aggregationOperator) {
    this->solveStatus = new SolveStatus(None);
    this->aggregationOperator = aggregationOperator;
    normalizer = new MinMaxNormalizer();
}

CriteriaAggregationMethod::CriteriaAggregationMethod(AggregationOperator* aggregationOperator, Normalizer* normalizer) {
    this->solveStatus = new SolveStatus(None);
    this->aggregationOperator = aggregationOperator;
    this->normalizer = normalizer;
}

CriteriaAggregationMethod::CriteriaAggregationMethod(MathModel *mathModel, WeightCriteriaRelation *relation, AggregationOperator* aggregationOperator) {
    this->solveStatus = new SolveStatus(None);
    setMathModel(mathModel);
    this->relation = relation->copy();
    this->aggregationOperator = aggregationOperator;
    normalizer = new MinMaxNormalizer();
}

CriteriaAggregationMethod::CriteriaAggregationMethod(MathModel *mathModel, WeightCriteriaRelation *relation, AggregationOperator* aggregationOperator, Normalizer* normalizer) {
    this->solveStatus = new SolveStatus(None);
    setMathModel(mathModel);
    this->relation = relation->copy();
    this->aggregationOperator = aggregationOperator;
    this->normalizer = normalizer;
}

CriteriaAggregationMethod::~CriteriaAggregationMethod() {
    if (mathModel != nullptr)
        delete mathModel;
    if (relation != nullptr)
        delete relation;
    if (normalizer != nullptr)
        delete normalizer;
    if (aggregationOperator != nullptr)
        delete aggregationOperator;
    if (solveStatus != nullptr)
        delete solveStatus;
}

void CriteriaAggregationMethod::setMathModel(MathModel *mathModel) {
    this->mathModel = new MathModel(*mathModel);
}

void CriteriaAggregationMethod::setCriteriaRelation(CriteriaRelation *relation) {
    this->relation = relation->copy();
}

void CriteriaAggregationMethod::setAggregationOperator(AggregationOperator *aggregationOperator) {
    this->aggregationOperator = aggregationOperator;
}

void CriteriaAggregationMethod::setNormalizer(Normalizer *normalizer) {
    delete this->normalizer;
    this->normalizer = normalizer;
}

SolveStatus *CriteriaAggregationMethod::solve() {
    if (solveStatus->getStatus() == DecisionStatus::Optimal)
        return solveStatus;

    delete solveStatus;
    solveStatus = new SolveStatus(None);

    // method check validity and convert relation to WeightCriteriaRelation
    calculateValiditySolveStatus();

    if (solveStatus->getStatus() != DecisionStatus::None)
        return solveStatus;

    if (aggregationOperator->isNeedNormalizedMathModel()) {
        auto normalizedMathModel = normalizer->getNormalizedMathModel(mathModel);

        if (!normalizedMathModel->isNormalized())
            return new SolveStatus(DecisionStatus::InvalidModel, "failed to normalize math model");

        delete mathModel;
        mathModel = normalizedMathModel;
    }

    estimateVectorWeight = aggregationOperator->getEstimateVectorMark(mathModel, (WeightCriteriaRelation* )relation);
    return this->solveStatus = new SolveStatus(Optimal);
}

void CriteriaAggregationMethod::calculateValiditySolveStatus() {
    if (mathModel == nullptr) {
        solveStatus = new SolveStatus(InvalidModel, "math model was null");
        return;
    }

    if (relation == nullptr) {
        solveStatus = new SolveStatus(InvalidData, "relation was null");
        return;
    }

    if (aggregationOperator == nullptr) {
        solveStatus = new SolveStatus(InvalidData, "aggregationOperator was null");
        return;
    }

    if ((relation = CriteriaRelationConverter::convertToWeightCriteriaRelation(relation)) == nullptr) {
        solveStatus = new SolveStatus(InvalidData, "relation cannot be reduces to AllCriteriaRelation");
        return;
    }

    if (!mathModel->isValid()) {
        solveStatus = new SolveStatus(InvalidModel, "invalid math model");
        return;
    }

    if (!relation->isValid()) {
        solveStatus = new SolveStatus(InvalidData, "criteria relationships are set incorrectly");
    }
}

std::map<int, double> CriteriaAggregationMethod::getEstimateVectorWeight() {
    return this->estimateVectorWeight;
}

int CriteriaAggregationMethod::getBestEstimateVectorId() {
    return aggregationOperator->getBestEstimateVectorId();
}
