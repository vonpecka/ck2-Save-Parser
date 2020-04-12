#include <parser.h>

#ifndef ENTITY_H
#define ENTITY_H

namespace ck2
{
struct Entity : Parser
{
    unsigned int ID;

    Dictionary<std::string, std::string> dictionary;

protected:
    std::string getStringfromDict(std::string key);

    float getFloatFromDict(std::string key);

    void parseData(std::vector<Pair<int, std::string>> data);
};
}

#endif // ENTITY_H
