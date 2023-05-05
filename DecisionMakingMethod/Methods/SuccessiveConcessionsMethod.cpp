#include "SuccessiveConcessionsMethod.h"
#include "../IntermediateMethodData/IntermediateMethodData/SuccessiveConcessionsIntermediateData.h"
#include "../DecisionMakerInfo/DecisionMakerInfo/CedeValueInfo.h"

SuccessiveConcessionsMethod::SuccessiveConcessionsMethod() {
    this->solveStatus = new SolveStatus(None);
    this->mathModel = nullptr;
    this->relation = nullptr;
}

SuccessiveConcessionsMethod::SuccessiveConcessionsMethod(MathModel *mathModel, CriteriaRelation *relation) {
    this->mathModel = new MathModel(*mathModel);
    this->relation = relation->copy();
    this->solveStatus = new SolveStatus(None);
}

SuccessiveConcessionsMethod::~SuccessiveConcessionsMethod() {
    if (mathModel != nullptr)
        delete mathModel;
    if (solveStatus != nullptr)
        delete solveStatus;
    if (relation != nullptr)
        delete relation;
}

SolveStatus *SuccessiveConcessionsMethod::solve() {
    if (solveStatus->getStatus() == DecisionStatus::Optimal ||
        solveStatus->getStatus() == DecisionStatus::Process ||
        solveStatus->getStatus() == DecisionStatus::Feasible)
        return solveStatus;

    delete solveStatus;
    solveStatus = new SolveStatus(None);

    calculateValiditySolveStatus();
    return solveStatus;
}

void SuccessiveConcessionsMethod::calculateValiditySolveStatus() {
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

SolveStatus *SuccessiveConcessionsMethod::makeIteration(DecisionMakerInfo* decisionMakingInfo) {
    auto status = solve();
    if (status->getStatus() != DecisionStatus::None &&
        status->getStatus() != DecisionStatus::Process)
        return status;

    status = new SolveStatus(DecisionStatus::Process);

    if (dynamic_cast<CedeValueInfo*>(decisionMakingInfo) == nullptr)
        return status;

    double delta = ((CedeValueInfo*) decisionMakingInfo)->getCedeValue();
    double max = 0, min = 0;
    int criteriaId = mathModel->getCriteriaArray()[criteriaNum]->getId();

    if (mathModel->getCriteriaArray()[criteriaNum]->getType() == CriteriaType::MAXIMIZATION) {
        max = mathModel->maxByCriteria(criteriaId);
        min = max - delta;
    } else {
        min = mathModel->minByCriteria(criteriaId);
        max = min + delta;
    }
    mathModel->deleteEstimateVectorByPredicate(criteriaNum, [](double mark, std::vector<double> attributes){
        return mark > attributes[1] || mark < attributes[0];
    }, {min, max});

    criteriaNum++;
    if (criteriaNum == mathModel->getCriteriaCount()) {
        status = new SolveStatus(DecisionStatus::Feasible);
    }
    if (mathModel->getEstimateVectorCount() < 1)
        status = new SolveStatus(DecisionStatus::Infeasible);

    if (mathModel->getEstimateVectorCount() == 1) {
        status = new SolveStatus(DecisionStatus::Optimal);
    }

    return status;
}

IntermediateMethodData *SuccessiveConcessionsMethod::getIntermediateMethodData() {
    return criteriaNum == mathModel->getEstimateVectorCount() ?
            nullptr:
            new SuccessiveConcessionsIntermediateData(mathModel->getCriteriaArray()[criteriaNum]);
}

void SuccessiveConcessionsMethod::setMathModel(MathModel *mathModel) {
    if (this->mathModel != nullptr)
        delete this->mathModel;
    this->mathModel = new MathModel(*mathModel);
}

void SuccessiveConcessionsMethod::setCriteriaRelation(CriteriaRelation *relation) {
    this->relation = relation->copy();
}

MathModel *SuccessiveConcessionsMethod::getMathModel() {
    return this->mathModel;
}

int SuccessiveConcessionsMethod::getBestEstimateVectorId() {
    return mathModel->getEstimateVectorCount() == 1 ? mathModel->getEstimateVectorArray()[0]->getId() : INT_MIN;
}
