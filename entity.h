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
    std::string getStringfromDict(std::string key)
    {
        if (!dictionary.at(key)) return std::string("");
        return remove(*dictionary.at(key), '"');
    }

    float getFloatFromDict(std::string key)
    {
        if (!dictionary.at(key)) return -1.f;
        return std::stof(*dictionary.at(key));
    }

    void parseData(std::vector<Pair<int, std::string>> data)
    {
        for (Pair<int, std::string> line : data) {
            StringPair property = getProperty(line.second);
            dictionary.push(property);
        }
    }
};
}

#endif // ENTITY_H
