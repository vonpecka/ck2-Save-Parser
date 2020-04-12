#include <entity.h>

#ifndef DYNASTIES_H
#define DYNASTIES_H

namespace ck2
{
//
// Object representing a Dynasty
//
struct Dynasty : public Entity
{
    friend class ParsedData;

    std::string name();
    std::string culture();
    std::string religion();
};

}
#endif // DYNASTIES_H
