#include "MathModel.h"

MathModel::MathModel(Criteria *criteriaArray, int criteriaCount, EstimateVector *estimateVectorArray,
                     int estimateVectorCount) {
    this->criteriaArray = criteriaArray;
    this->criteriaCount = criteriaCount;
    this->estimateVectorArray = estimateVectorArray;
    this->estimateVectorCount = estimateVectorCount;
}

Criteria *MathModel::getCriteriaArray() {
    return criteriaArray;
}

EstimateVector *MathModel::getEstimateVectorArray() {
    return estimateVectorArray;
}

int MathModel::getCriteriaCount() {
    return criteriaCount;
}

int MathModel::getEstimateVectorCount() {
    return estimateVectorCount;
}

double MathModel::sumByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double sum = 0;
    for (int i = 0; i < estimateVectorCount; ++i) {
        sum += estimateVectorArray[i].getMarks()[criteriaNum];
    }
    return sum;
}

double MathModel::sumByCriteria(std::string criteriaName) {
    int criteriaNum = findCriteriaNumByName(criteriaName);
    double sum = 0;
    for (int i = 0; i < estimateVectorCount; ++i) {
        sum += estimateVectorArray[i].getMarks()[criteriaNum];
    }
    return sum;
}

double MathModel::minByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double min = estimateVectorArray[0].getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        if (min < estimateVectorArray[i].getMarks()[criteriaNum])
            min = estimateVectorArray[i].getMarks()[criteriaNum];
    }
    return min;
}

double MathModel::minByCriteria(std::string criteriaName) {
    int criteriaNum = findCriteriaNumByName(criteriaName);
    double min = estimateVectorArray[0].getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        if (min < estimateVectorArray[i].getMarks()[criteriaNum])
            min = estimateVectorArray[i].getMarks()[criteriaNum];
    }
    return min;
}

double MathModel::maxByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double max = estimateVectorArray[0].getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        if (max > estimateVectorArray[i].getMarks()[criteriaNum])
            max = estimateVectorArray[i].getMarks()[criteriaNum];
    }
    return max;
}

double MathModel::maxByCriteria(std::string criteriaName) {
    int criteriaNum = findCriteriaNumByName(criteriaName);
    double max = estimateVectorArray[0].getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        if (max > estimateVectorArray[i].getMarks()[criteriaNum])
            max = estimateVectorArray[i].getMarks()[criteriaNum];
    }
    return max;
}

int MathModel::findCriteriaNumById(int criteriaId) {
    for (int i = 0; i < criteriaCount; ++i)
        if (criteriaArray[i].getId() == criteriaId)
            return i;
    return -1;
}

int MathModel::findCriteriaNumByName(std::string criteriaName) {
    for (int i = 0; i < criteriaCount; ++i)
        if (criteriaArray[i].getName() == criteriaName)
            return i;
    return -1;
}
