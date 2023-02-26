#ifndef DMLTESTER_ESTIMATEVECTOR_H
#define DMLTESTER_ESTIMATEVECTOR_H
#include <iostream>

//Векторная оценка альтернатив
class EstimateVector {
private:
    int id;
    std::string name;
    double* marks;
    int criteriaCount;
public:
    EstimateVector(int id, std::string name, double* markArray, int criteriaCount);
    int getId();
    std::string getName();
    double* getMarks();
    int getCriteriaCount();
};


#endif //DMLTESTER_ESTIMATEVECTOR_H
