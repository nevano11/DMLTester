#include "MathModel/Components/EstimateVector.h"
#include "DecisionMakingMethod/Methods/LexicographicOptimization.h"
#include "CriteriaRelation/Relations/AllCriteriaRelation.h"
#include "CriteriaRelation/Relations/SimpleCriteriaRelation.h"
#include "CriteriaRelation/Relations/WeightCriteriaRelation.h"
#include "CriteriaRelation/Relations/WeightCriteriaRelations/SimpleRankingMethod.h"
#include "MathModel/Components/Criteria.h"
#include "CriteriaRelation/Relations/WeightCriteriaRelations/ProportionalMethod.h"
#include "MathModel/Converters/Normalizers/MinMaxNormalizer.h"
#include "DecisionMakingMethod/Methods/AuxiliaryMethods/AggregationOperators/AddictiveAggregationOperator.h"

using namespace std;

int main() {
    // Для каждого метода
    int criteriaCount = 6;
    Criteria** criteriaArray = new Criteria*[criteriaCount];
    criteriaArray[0] = new Criteria(1, "f1");
    criteriaArray[1] = new Criteria(2, "f2");
    criteriaArray[2] = new Criteria(3, "f3", CriteriaType::MINIMIZATION);
    criteriaArray[3] = new Criteria(4, "f4", CriteriaType::MINIMIZATION);
    criteriaArray[4] = new Criteria(5, "f5");
    criteriaArray[5] = new Criteria(6, "f6", CriteriaType::MINIMIZATION);

    int alternativeCount = 7;
    EstimateVector** pEstimateVectorArray = new EstimateVector*[alternativeCount];
    
    pEstimateVectorArray[0] = new EstimateVector(1, "x1", new double [] {200, 10, -5, -5, 4, -45}, criteriaCount);
    pEstimateVectorArray[1] = new EstimateVector(2, "x2", new double [] {180, 8, -3, -4, 5, -48}, criteriaCount);
    pEstimateVectorArray[2] = new EstimateVector(3, "x3", new double [] {200, 8, -2, -5, 5, -50}, criteriaCount);
    pEstimateVectorArray[3] = new EstimateVector(4, "x4", new double [] {190, 10, -5, -3, 4, -48}, criteriaCount);
    pEstimateVectorArray[4] = new EstimateVector(5, "x5", new double [] {220, 12, -3, -3, 5, -50}, criteriaCount);
    pEstimateVectorArray[5] = new EstimateVector(6, "x6", new double [] {200, 7, -2, -4, 3, -42}, criteriaCount);
    pEstimateVectorArray[6] = new EstimateVector(7, "x7", new double [] {220, 15, -5, -2, 4, -35}, criteriaCount);

    MathModel* mathModel = new MathModel(criteriaArray, criteriaCount, pEstimateVectorArray, alternativeCount);
    std::cout << "Start MM\n";
    std::cout << mathModel->estimateVectorArrayToString();

    WeightCriteriaRelation* relation = new ProportionalMethod(
            criteriaArray,
            criteriaCount,
            std::map<int, double> {
                    { 1, 4 },
                    { 2, 1.5 },
                    { 3, 1.5 },
                    { 4, 6 },
                    { 5, 3 },
                    { 6, 5 }
            });

    Normalizer* normalizer = new MinMaxNormalizer();
    auto normalizedMathModel = normalizer->getNormalizedMathModel(mathModel);
    cout << endl << normalizedMathModel->estimateVectorArrayToString();

    AggregationOperator* addregationOperator = new AddictiveAggregationOperator();
    auto res = addregationOperator->getEstimateVectorMark(normalizedMathModel, relation);

    cout << endl;
    for (const auto &item: res) {
        cout << item.first << " " << item.second << endl;
    }

    delete addregationOperator;
    delete normalizer;
    delete relation;
    delete[] criteriaArray;
    delete[] pEstimateVectorArray;
    delete mathModel;

    return 0;
}
