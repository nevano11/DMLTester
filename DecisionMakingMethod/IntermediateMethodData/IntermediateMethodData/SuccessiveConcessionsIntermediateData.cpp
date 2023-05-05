#include "SuccessiveConcessionsIntermediateData.h"

SuccessiveConcessionsIntermediateData::SuccessiveConcessionsIntermediateData(Criteria *criteriaThatNeedCedeValue) {
    criteria = criteriaThatNeedCedeValue;
}

Criteria *SuccessiveConcessionsIntermediateData::getCriteriaThatNeedCedeValue() {
    return criteria;
}

std::string SuccessiveConcessionsIntermediateData::toString() {
    return "Criteria with id=" + std::to_string(criteria->getId());
}
