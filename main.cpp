#include "MathModel/Components/EstimateVector.h"
#include "DecisionMakingMethod/Methods/LexicographicOptimization.h"
#include "DecisionMakingMethod/Methods/CriteriaAggregationMethod.h"
#include "CriteriaRelation/Relations/AllCriteriaRelation.h"
#include "CriteriaRelation/Relations/SimpleCriteriaRelation.h"
#include "CriteriaRelation/Relations/WeightCriteriaRelation.h"
#include "CriteriaRelation/Relations/WeightCriteriaRelations/SimpleRankingMethod.h"
#include "MathModel/Components/Criteria.h"
#include "CriteriaRelation/Relations/WeightCriteriaRelations/ProportionalMethod.h"
#include "MathModel/Converters/Normalizers/MinMaxNormalizer.h"
#include "DecisionMakingMethod/Methods/AuxiliaryMethods/AggregationOperators/AddictiveAggregationOperator.h"
#include "DecisionMakingMethod/Methods/AuxiliaryMethods/AggregationOperators/MultiplicativeAggregationOperator.h"
#include "DecisionMakingMethod/Methods/AuxiliaryMethods/AggregationOperators/IdealDistanceAggregationOperator.h"
#include "Solver/MultiCriteriaMethodSolver/OneStepMultiCriteriaMethodSolver.h"
#include "DecisionMakingMethod/Methods/SuccessiveConcessionsMethod.h"
#include "DecisionMakingMethod/DecisionMakerInfo/DecisionMakerInfo/CedeValueInfo.h"

using namespace std;

void doTmth(void (*printFunction)(MathModel* mm), MathModel* mathModel) {
    cout << "Start mathModel\n";
    printFunction(mathModel);
    cout << "================\n";
}

int main() {
    auto a = [] (MathModel* mathModel) {
        std::cout << mathModel->estimateVectorArrayToString();
    };

    // Для каждого метода
    int criteriaCount = 4;
    Criteria** criteriaArray = new Criteria*[criteriaCount];
    criteriaArray[0] = new Criteria(1, "f1", CriteriaType::MINIMIZATION);
    criteriaArray[1] = new Criteria(2, "f2", CriteriaType::MINIMIZATION);
    criteriaArray[2] = new Criteria(3, "f3", CriteriaType::MINIMIZATION);
    criteriaArray[3] = new Criteria(4, "f4", CriteriaType::MINIMIZATION);

    int alternativeCount = 7;
    EstimateVector** pEstimateVectorArray = new EstimateVector*[alternativeCount];
    
    pEstimateVectorArray[0] = new EstimateVector(1, "x1", new double [] {220, -50, -52, -8}, criteriaCount);
    pEstimateVectorArray[1] = new EstimateVector(2, "x2", new double [] {180, -80, -35, -5}, criteriaCount);
    pEstimateVectorArray[2] = new EstimateVector(3, "x3", new double [] {240, -60, -47, -10}, criteriaCount);
    pEstimateVectorArray[3] = new EstimateVector(4, "x4", new double [] {240, -100, -40, -10}, criteriaCount);
    pEstimateVectorArray[4] = new EstimateVector(5, "x5", new double [] {200, -50, -50, -8}, criteriaCount);
    pEstimateVectorArray[5] = new EstimateVector(6, "x6", new double [] {150, -25, -40, -8}, criteriaCount);
    pEstimateVectorArray[6] = new EstimateVector(7, "x7", new double [] {180, -60, -50, -8}, criteriaCount);

    MathModel* mathModel = new MathModel(criteriaArray, criteriaCount, pEstimateVectorArray, alternativeCount);

    CriteriaRelation* relation = new SimpleRankingMethod(
            criteriaCount,
            {{1, 1.5}, {2, 1.5}, {3, 3.5}, {4, 3.5}}
            );

    relation = CriteriaRelationConverter::convertToWeightCriteriaRelation(relation);

    relation = CriteriaRelationConverter::convertToSimpleCriteriaRelation(relation);

    int relationCount = ((SimpleCriteriaRelation* )relation)->getRelationCount();
    auto relations = ((SimpleCriteriaRelation* )relation)->getTwoCriteriaRelationArray();
    for (int i = 0; i < relationCount; ++i) {
        cout << relations[i]->getFirstCriteriaId();
        switch (relations[i]->getConstraint()) {
            case CriteriaConstraint::More:
                cout << " > ";
                break;
            case CriteriaConstraint::Less:
                cout << " < ";
                break;
            case CriteriaConstraint::MoreOrEquivalent:
                cout << " >= ";
                break;
            case CriteriaConstraint::LessOrEquivalent:
                cout << " <= ";
                break;
            case CriteriaConstraint::Equivalent:
                cout << " ~ ";
                break;
        }
        cout << relations[i]->getSecondCriteriaId();
        cout << endl;
    }

    delete relation;
    delete[] criteriaArray;
    delete[] pEstimateVectorArray;
    delete mathModel;

    return 0;
}

// OneStepSolver

//    OneStepMultiCriteriaMethodSolver* solver = new OneStepMultiCriteriaMethodSolver(mathModel, relation);
//    solver->addMethod(new CriteriaAggregationMethod(new MultiplicativeAggregationOperator(), new MinMaxNormalizer()));
//    solver->addMethod(new LexicographicOptimization());
//    solver->addMethod(new CriteriaAggregationMethod(new MultiplicativeAggregationOperator()));
//    solver->addMethod(new LexicographicOptimization());
//    auto mathodStatusMap = solver->solve();
//
//    for (const auto& [key, value] : mathodStatusMap) {
//
//        if (dynamic_cast<LexicographicOptimization*>(key) != nullptr) {
//            std::cout << "LexicographicOptimization";
//        }
//        if (dynamic_cast<CriteriaAggregationMethod*>(key) != nullptr) {
//            std::cout << "CriteriaAggregationMethod";
//        }
//        cout << (value->getStatus() == DecisionStatus::Optimal ? " Optimal" : " Bad");
//        cout << " Best alternative has id = " << key->getBestEstimateVectorId() << endl;
//    }


// Multi Criteria Method

//    SuccessiveConcessionsMethod* method = new SuccessiveConcessionsMethod(mathModel, relation);
//    SolveStatus* solveStatus = method->solve();
//    double cedeValue = 0;
//
//    while (solveStatus->getStatus() != DecisionStatus::Optimal && solveStatus->getStatus() != DecisionStatus::Feasible) {
//        doTmth(a, method->getMathModel());
//        cout << solveStatus->toString() << endl;
//        if (method->getIntermediateMethodData() != nullptr)
//            cout << method->getIntermediateMethodData()->toString() << endl;
//        cout << "Enter cede value ";
//        cin >> cedeValue;
//        cout << endl;
//        solveStatus = method->makeIteration(new CedeValueInfo(cedeValue));
//    }
