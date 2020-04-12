#include "dynasties.h"

namespace ck2
{
    std::string Dynasty::name()
    {
        return getStringfromDict("name");
    }

    std::string Dynasty::culture()
    {
        return getStringfromDict("culture");
    }

    std::string Dynasty::religion()
    {
        return getStringfromDict("religion");
    }
};
