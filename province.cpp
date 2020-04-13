#include "province.h"

namespace ck2
{
    std::string Province::culture()
    {
        return getStringfromDict("culture");
    }

    std::string Province::religion()
    {
        return getStringfromDict("religion");
    }
};
