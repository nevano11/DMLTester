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
    this->type = CriteriaType::MAXIMIZATION;
}

Criteria::Criteria(const Criteria &other) : id(other.id), name(other.name), type(other.type)
{
}

Criteria::~Criteria()
{
}

int Criteria::getId()
{
    return id;
}

std::string Criteria::getName() {
    return name;
}

CriteriaType Criteria::getType() {
    return type;
}
