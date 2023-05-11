#ifndef DMLTESTER_SIMPLECRITERIARELATIONUTIL_H
#define DMLTESTER_SIMPLECRITERIARELATIONUTIL_H

#include "Node.h"
#include "../SimpleCriteriaRelation.h"

class SimpleCriteriaRelationUtil {
private:
    Node* root;
    bool isValid = true;
public:
    SimpleCriteriaRelationUtil(SimpleCriteriaRelation* simpleCriteriaRelation);
};


#endif //DMLTESTER_SIMPLECRITERIARELATIONUTIL_H
