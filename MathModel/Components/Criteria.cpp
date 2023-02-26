#include "Criteria.h"

#include <utility>

Criteria::Criteria(int id, std::string name, CriteriaType criteriaType) {
    this->id = id;
    this->name = std::move(name);
    this->type = criteriaType;
}

Criteria::Criteria(int id, std::string name) {
    this->id = id;
    this->name = std::move(name);
    this->type = MAXIMIZATION;
}

int Criteria::getId() {
    return id;
}

std::string Criteria::getName() {
    return name;
}

CriteriaType Criteria::getType() {
    return type;
}
