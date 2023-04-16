#include "LexicographicOptimization.h"

LexicographicOptimization::LexicographicOptimization()
{
    this->solveStatus = new SolveStatus(None);
}

LexicographicOptimization::LexicographicOptimization(MathModel *mathModel, CriteriaRelation *relation)
{
    this->mathModel = new MathModel(*mathModel);
    this->relation = relation;
    this->solveStatus = new SolveStatus(None);
}

LexicographicOptimization::~LexicographicOptimization()
{
    if (mathModel != nullptr)
        delete mathModel;
    if (solveStatus != nullptr)
        delete solveStatus;
    if (relation != nullptr)
        delete relation;
}

SolveStatus* LexicographicOptimization::solve() {
    if (solveStatus->getStatus() == DecisionStatus::Optimal)
        return solveStatus;

    delete solveStatus;
    solveStatus = new SolveStatus(None);

    calculateValiditySolveStatus();
    if (solveStatus->getStatus() != DecisionStatus::None)
        return solveStatus;

    int count = ((AllCriteriaRelation*) relation)->getSequenceSize();
    int* sequence = ((AllCriteriaRelation*) relation)->getIdSequence();
    for (size_t i = 0; i < count; i++)
    {
        int cid = sequence[i];
        Criteria* mainCriteria = mathModel->getCriteriaById(cid);

        double thresholdValue = mainCriteria->getType() == CriteriaType::MAXIMIZATION ?
            mathModel->maxByCriteria(cid):
            mathModel->minByCriteria(cid);
        
        int criteriaNum = mathModel->findCriteriaNumById(cid);

        std::cout << "Подход\n";
        std::cout << "CriteriaNum=" << criteriaNum << " thresholdValue=" << thresholdValue << "\n";
        mathModel->deleteEstimateVectorIfMarkNotEqualValue(criteriaNum, thresholdValue);
        std::cout << mathModel->estimateVectorArrayToString() << "\n";

        if (mathModel->getEstimateVectorCount() == 1)
            break;
    }

    return this->solveStatus = new SolveStatus(Optimal);
}

MathModel* LexicographicOptimization::getMathModel() {
    return this->mathModel;
}

void LexicographicOptimization::setMathModel(MathModel *mathModel) {
    delete mathModel;
    this->mathModel = new MathModel(*mathModel);
}

void LexicographicOptimization::setCriteriaRelation(CriteriaRelation *relation) {
    this->relation = CriteriaRelationConverter::convertToAllCriteriaRelation(relation);
}

void LexicographicOptimization::calculateValiditySolveStatus() {
    if (mathModel == nullptr) {
        solveStatus = new SolveStatus(InvalidModel, "math model was null");
        return;
    }

    if (relation == nullptr) {
        solveStatus = new SolveStatus(InvalidData, "relation was null");
        return;
    }

    if ((relation = CriteriaRelationConverter::convertToAllCriteriaRelation(relation)) == nullptr) {
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

int LexicographicOptimization::getBestEstimateVectorId() {
    return mathModel->getEstimateVectorCount() == 1 ? mathModel->getCriteriaArray()[0]->getId() : INT_MIN;
}
