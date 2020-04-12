#include "titles.h"

namespace ck2
{
    std::string Title::succession()
    {
        return getStringfromDict("succession");
    }

    std::string Title::gender()
    {
        return getStringfromDict("gender");
    }

    unsigned int Title::holderID()
    {
        return (int)getFloatFromDict("holder");
    }
}
