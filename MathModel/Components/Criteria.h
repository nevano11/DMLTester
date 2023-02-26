#ifndef DMLTESTER_CRITERIA_H
#define DMLTESTER_CRITERIA_H

#include <iostream>

enum CriteriaType {MAXIMIZATION, MINIMIZATION};

class Criteria {
private:
    int id;
    std::string name;
    CriteriaType type;
public:
    Criteria(int id, std::string name, CriteriaType criteriaType);
    Criteria(int id, std::string name);
    int getId();
    std::string getName();
    CriteriaType getType();
};

#endif //DMLTESTER_CRITERIA_H
