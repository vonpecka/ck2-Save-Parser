#include "entity.h"


namespace ck2
{
    std::string Entity::getStringfromDict(std::string key)
    {
        if (!dictionary.at(key)) return std::string("");
        return remove(*dictionary.at(key), '"');
    }

    float Entity::getFloatFromDict(std::string key)
    {
        if (!dictionary.at(key)) return -1.f;
        return std::stof(*dictionary.at(key));
    }

    void Entity::parseData(std::vector<Pair<int, std::string>> data)
    {
        for (Pair<int, std::string> line : data) {
            StringPair property = getProperty(line.second);
            dictionary.push(property);
        }
    }
}
