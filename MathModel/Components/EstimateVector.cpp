#include "EstimateVector.h"

EstimateVector::EstimateVector(int id, std::string name, double *markArray, int criteriaCount) {
    // если criteria count < 0 Exception
    // copying markArray
    this->id = id;
    this->name = name;
    this->marks = markArray;
    this->criteriaCount = criteriaCount;
}

int EstimateVector::getId() {
    return id;
}

std::string EstimateVector::getName() {
    return name;
}

double *EstimateVector::getMarks() {
    return marks;
}

int EstimateVector::getCriteriaCount() {
    return this->criteriaCount;
}
