#include "CedeValueInfo.h"

CedeValueInfo::CedeValueInfo(double cedeValue) {
    this->cedeValue = cedeValue;
}

double CedeValueInfo::getCedeValue() {
    return cedeValue < 0 ? 0 : cedeValue;
}
