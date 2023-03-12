#include "LexicographicOptimization.h"

LexicographicOptimization::LexicographicOptimization()
{
    this->solveStatus = new SolveStatus(None);
}

LexicographicOptimization::LexicographicOptimization(MathModel *mathModel, AllCriteriaRelation *relation)
{
    this->mathModel = new MathModel(*mathModel);
    this->relation = relation;
    this->solveStatus = new SolveStatus(None);
}

LexicographicOptimization::~LexicographicOptimization()
{
    delete mathModel;
    delete solveStatus;
    delete relation;
}

SolveStatus* LexicographicOptimization::solve() {
    if (solveStatus->getStatus() != DecisionStatus::None)
        return solveStatus;

    if (!mathModel->isValid()) {
        solveStatus = new SolveStatus(InvalidModel, "invalid math model");
        return solveStatus;
    }

    if (!relation->isValid()) {
        solveStatus = new SolveStatus(InvalidData, "criteria relationships are set incorrectly");
        return solveStatus;
    }

    int count = relation->getSequenceSize();
    int* sequence = relation->getIdSequence();
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
