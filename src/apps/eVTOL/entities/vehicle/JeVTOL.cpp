#include "JeVTOL.h"

namespace joby {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Aircraft::Aircraft(double cruiseSpeed, double batteryCapacity, double chargeTime, double energyUse, size_t maxPassengerCount, double failureRate):
    m_cruiseSpeed(cruiseSpeed),
    m_batteryCapacity(batteryCapacity),
    m_chargeTime(chargeTime),
    m_energyUse(energyUse),
    m_maxPassengerCount(maxPassengerCount),
    m_failureRate(failureRate)
{
}

Aircraft::~Aircraft()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing
