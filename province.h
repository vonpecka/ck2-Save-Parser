#include <entity.h>

#ifndef PROVINCE_H
#define PROVINCE_H

namespace ck2
{
//
// Object representing a Dynasty
//
struct Province : public Entity
{
    friend class ParsedData;

    std::string culture();
    std::string religion();
};

}

#endif // PROVINCE_H
