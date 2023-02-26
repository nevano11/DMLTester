#include "MathModel/Components/EstimateVector.h"

int main() {
    double* marks = new double[10];
    for (int i = 0; i < 10; ++i) {
        marks[i] = i;
    }

    EstimateVector* vector = new EstimateVector(1, "x1", marks, 10);

    double* marks2 = vector->getMarks();
    for (int i = 0; i < 10; ++i) {
        std::cout << (marks2[i] *= 2) << " " << marks[i] << std::endl;
    }
    return 0;
}
