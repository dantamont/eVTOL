#include "JCompany.h"

namespace joby {
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Company::Company(const std::string & name, const Aircraft & specification):
    m_name(name),
    m_aircraftSpec(specification)
{
}

Company::~Company()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // end namespacing