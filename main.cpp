#include "MathModel/Components/EstimateVector.h"
#include "DecisionMakingMethod/Methods/LexicographicOptimization.h"
#include "CriteriaRelation/Relations/AllCriteriaRelation.h"

int main() {
    // Для каждого метода
    int criteriaCount = 3;
    Criteria** criteriaArray = new Criteria*[criteriaCount];
    criteriaArray[0] = new Criteria(1, "f1");
    criteriaArray[1] = new Criteria(2, "f2");
    criteriaArray[2] = new Criteria(3, "f3");

    int alternativeCount = 3;
    EstimateVector** pEstimateVectorArray = new EstimateVector*[alternativeCount];

    double* marks1 = new double[criteriaCount]; 
    marks1[0] = 0.9;
    marks1[1] = 15;
    marks1[2] = 1;

    double* marks2 = new double[criteriaCount]; 
    marks2[0] = 0.9;
    marks2[1] = 8;
    marks2[2] = 6;

    double* marks3 = new double[criteriaCount]; 
    marks3[0] = 0.8;
    marks3[1] = 6;
    marks3[2] = 0;
    
    pEstimateVectorArray[0] = new EstimateVector(1, "x1", marks1, criteriaCount);
    pEstimateVectorArray[1] = new EstimateVector(2, "x2", marks2, criteriaCount);
    pEstimateVectorArray[2] = new EstimateVector(3, "x3", marks3, criteriaCount);

    MathModel* mathModel = new MathModel(criteriaArray, criteriaCount, pEstimateVectorArray, alternativeCount);
    std::cout << "Start MM\n";
    std::cout << mathModel->estimateVectorArrayToString();

    AllCriteriaRelation* aCR = new AllCriteriaRelation(criteriaArray, criteriaCount, new int[criteriaCount] {1, 2, 3});

    LexicographicOptimization* method = new LexicographicOptimization(mathModel, aCR);

    method->solve();

    std::cout << "Result:\n";
    int resultsCount = method->getMathModel()->getEstimateVectorCount();
    for (size_t i = 0; i < resultsCount; i++)
    {
        auto vector = method->getMathModel()->getEstimateVectorArray()[i];
        std::cout << vector->toString() << "\n";
    }

    delete[] marks1;
    delete[] marks2;
    delete[] marks3;

    delete[] criteriaArray;
    delete[] pEstimateVectorArray;
    delete mathModel;
    delete aCR;
    delete method;

    return 0;
}
