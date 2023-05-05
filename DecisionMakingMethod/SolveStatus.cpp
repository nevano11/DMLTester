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

std::string SolveStatus::toString() {
    std::string status;
    switch (decisionStatus) {
        case None:
            status = "None";
            break;
        case Process:
            status = "Process";
            break;
        case Optimal:
            status = "Optimal";
            break;
        case Feasible:
            status = "Feasible";
            break;
        case Infeasible:
            status = "Infeasible";
            break;
        case InvalidModel:
            status = "InvalidModel";
            break;
        case InvalidData:
            status = "InvalidData";
            break;
    }
    return "Status=" + status + " message=" + getMessage();
}
