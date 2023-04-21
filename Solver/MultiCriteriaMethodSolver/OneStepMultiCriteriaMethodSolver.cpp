#include "OneStepMultiCriteriaMethodSolver.h"

OneStepMultiCriteriaMethodSolver::OneStepMultiCriteriaMethodSolver(MathModel *mathModel, CriteriaRelation *relation) {
    this->mathModel = mathModel;
    this->relation = relation;
}

OneStepMultiCriteriaMethodSolver::~OneStepMultiCriteriaMethodSolver() {
    for (const auto &item: methods) {
        if (item != nullptr)
            delete item;
    }
    if (mathModel != nullptr)
        delete mathModel;
    if (relation != nullptr)
        delete relation;
}

void OneStepMultiCriteriaMethodSolver::addMethod(OneStepMethod* method) {
    methods.push_back(method);
}

void OneStepMultiCriteriaMethodSolver::addMethods(std::list<OneStepMethod*> methods) {
    for (const auto &method: methods) {
        addMethod(method);
    }
}

std::map<OneStepMethod*, SolveStatus*> OneStepMultiCriteriaMethodSolver::solve() {
    std::map<OneStepMethod*, SolveStatus*> result;

    for (const auto &method: methods) {
        method->setMathModel(mathModel);
        method->setCriteriaRelation(relation);

        result.emplace(method, method->solve());
    }
    return result;
}