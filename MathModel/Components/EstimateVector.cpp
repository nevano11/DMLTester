#include "EstimateVector.h"

EstimateVector::EstimateVector(int id, std::string name, double *markArray, int criteriaCount) {
    this->id = id;
    this->name = name;
    marks = new double[criteriaCount];
    for (int i = 0; i < criteriaCount; i++) {
        marks[i] = markArray[i];
    }
    this->criteriaCount = criteriaCount;
}

EstimateVector::EstimateVector(const EstimateVector &other) {
    this->id = other.id;
    this->name = other.name;
    this->criteriaCount = other.criteriaCount;
    marks = new double[criteriaCount];
    for (int i = 0; i < criteriaCount; i++) {
        marks[i] = other.marks[i];
    }
}

EstimateVector::~EstimateVector()
{
    delete[] marks;
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

std::string EstimateVector::toString() {
    std::string res = "EstimateVector[";
    res += "id=" + std::to_string(this->id);
    res += ", name=" + name;

    res += ", marks=[";
    for (int i = 0; i < criteriaCount; ++i) {
        res += std::to_string(marks[i]);
        res += " ";
    }
    res += "]]";
    return res;
}
