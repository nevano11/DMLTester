#include <cmath>
#include "MathModel.h"

MathModel::MathModel(Criteria **criteriaArray, int criteriaCount, EstimateVector **estimateVectorArray,
                     int estimateVectorCount) {
    this->criteriaArray = criteriaArray;
    this->criteriaCount = criteriaCount;
    this->estimateVectorArray = estimateVectorArray;
    this->estimateVectorCount = estimateVectorCount;
}

MathModel::MathModel(const MathModel &other)
{
    criteriaCount = other.criteriaCount;
    criteriaArray = new Criteria*[criteriaCount];
    for (int i = 0; i < criteriaCount; i++) {
        criteriaArray[i] = new Criteria(*other.criteriaArray[i]);
    }
        
    estimateVectorCount = other.estimateVectorCount;
    estimateVectorArray = new EstimateVector*[estimateVectorCount];
    for (int i = 0; i < estimateVectorCount; i++) {
        estimateVectorArray[i] = new EstimateVector(*other.estimateVectorArray[i]);
    }
}

MathModel::~MathModel()
{
    for (int i = 0; i < criteriaCount; i++) {
        delete criteriaArray[i];
    }
    delete[] criteriaArray;

    for (int i = 0; i < estimateVectorCount; i++) {
        delete estimateVectorArray[i];
    }
    delete[] estimateVectorArray;
}

Criteria **MathModel::getCriteriaArray() {
    return criteriaArray;
}

EstimateVector **MathModel::getEstimateVectorArray() {
    return estimateVectorArray;
}

int MathModel::getCriteriaCount() {
    return criteriaCount;
}

int MathModel::getEstimateVectorCount() {
    return estimateVectorCount;
}

Criteria *MathModel::getCriteriaById(int id)
{
    return criteriaArray[findCriteriaNumById(id)];
}

Criteria *MathModel::getCriteriaByName(std::string name)
{
    return criteriaArray[findCriteriaNumByName(name)];
}

double MathModel::sumByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double sum = 0;
    for (int i = 0; i < estimateVectorCount; ++i) {
        sum += estimateVectorArray[i]->getMarks()[criteriaNum];
    }
    return sum;
}

double MathModel::sumByCriteria(std::string criteriaName) {
    int criteriaNum = findCriteriaNumByName(criteriaName);
    double sum = 0;
    for (int i = 0; i < estimateVectorCount; ++i) {
        sum += estimateVectorArray[i]->getMarks()[criteriaNum];
    }
    return sum;
}

double MathModel::minByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double min = estimateVectorArray[0]->getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        int mark = estimateVectorArray[i]->getMarks()[criteriaNum];
        if (min > mark)
            min = mark;
    }
    return min;
}

double MathModel::minByCriteria(std::string criteriaName) {
    int criteriaNum = findCriteriaNumByName(criteriaName);
    double min = estimateVectorArray[0]->getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        int mark = estimateVectorArray[i]->getMarks()[criteriaNum];
        if (min > mark)
            min = mark;
    }
    return min;
}

double MathModel::maxByCriteria(int criteriaId) {
    int criteriaNum = findCriteriaNumById(criteriaId);
    double max = estimateVectorArray[0]->getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        int mark = estimateVectorArray[i]->getMarks()[criteriaNum];
        if (max < mark)
            max = mark;
    }
    return max;
}

double MathModel::maxByCriteria(std::string criteriaName) {
    int criteriaNum = findCriteriaNumByName(criteriaName);
    double max = estimateVectorArray[0]->getMarks()[criteriaNum];
    for (int i = 1; i < estimateVectorCount; ++i) {
        int mark = estimateVectorArray[i]->getMarks()[criteriaNum];
        if (max < mark)
            max = mark;
    }
    return max;
}

int MathModel::findCriteriaNumById(int criteriaId) {
    for (int i = 0; i < criteriaCount; ++i)
        if (criteriaArray[i]->getId() == criteriaId)
            return i;
    return -1;
}

int MathModel::findCriteriaNumByName(std::string criteriaName) {
    for (int i = 0; i < criteriaCount; ++i)
        if (criteriaArray[i]->getName() == criteriaName)
            return i;
    return -1;
}

void MathModel::deleteEstimateVectorIfMarkNotEqualValue(int criteriaNum, double value)
{
    int deleteCount = 0;
    for (int i = 0; i < estimateVectorCount; i++)
        if (!isDoubleEqual(estimateVectorArray[i]->getMarks()[criteriaNum], value))
            deleteCount++;

    estimateVectorCount = estimateVectorCount - deleteCount;
    EstimateVector** tmpArray = new EstimateVector*[estimateVectorCount];

    int j = 0;
    for (size_t i = 0; i < estimateVectorCount + deleteCount; i++) {
        if (isDoubleEqual(estimateVectorArray[i]->getMarks()[criteriaNum], value))
            tmpArray[j++] = new EstimateVector(*estimateVectorArray[i]);
        delete estimateVectorArray[i];
    }
    delete[] estimateVectorArray;
    estimateVectorArray = tmpArray;
}


bool MathModel::isValid()
{
    if (criteriaCount < 1 || estimateVectorCount < 1 || criteriaArray == nullptr || estimateVectorArray == nullptr)
        return false;

    for (size_t i = 0; i < criteriaCount; i++)
        if (criteriaArray[i] == nullptr)
            return false;
    
    for (size_t i = 0; i < estimateVectorCount; i++)
        if (estimateVectorArray[i] == nullptr || estimateVectorArray[i]->getCriteriaCount() != criteriaCount)
            return false;

    return true;
}

std::string MathModel::estimateVectorArrayToString() {
    std::string res = "";
    for (int i = 0; i < estimateVectorCount; ++i) {
        res += estimateVectorArray[i]->toString();
        res += "\n";
    }
    return res;
}

bool MathModel::isDoubleEqual(double a, double b) {
    bool res = std::fabs(a - b) < std::numeric_limits<double>::epsilon();
    return res;
}

bool MathModel::isNormalized() {
    for (int i = 0; i < estimateVectorCount; ++i)
        for (int j = 0; j < criteriaCount; ++j)
            if (estimateVectorArray[i]->getMarks()[j] > 1 || estimateVectorArray[i]->getMarks()[j] < 0)
                return false;
    return true;
}
