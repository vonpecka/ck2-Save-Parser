#include <entity.h>

#ifndef TITLES_H
#define TITLES_H
namespace ck2
{

//
// Object representing a Title
//
struct Title : public Entity
{
    friend class ParsedData;
    std::string succession();
    std::string gender();
    unsigned int holderID();
};

}
#endif // TITLES_H
