#include "SolveStatus.h"

SolveStatus::SolveStatus()
{
}

SolveStatus::SolveStatus(DecisionStatus decisionStatus)
{
    this->decisionStatus = decisionStatus;
}

SolveStatus::SolveStatus(DecisionStatus decisionStatus, std::string message)
{
    this->decisionStatus = decisionStatus;
    this->message = message;
}

DecisionStatus SolveStatus::getStatus()
{
    return decisionStatus;
}

std::string SolveStatus::getMessage()
{
    return message;
}
