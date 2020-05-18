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
        int level = 0;
        std::vector<Pair<int, std::string>> subentityData;
        std::string subentityName;

        for (Pair<int, std::string> line : data) {
            if (contains(line.second, '{')) {
                if (level==1) {
                    subentityName = getProperty(line.second).first;
                }
                level++;
            }
            if (level==1) {
                StringPair property = getProperty(line.second);
                dictionary.push(property);
            }
            if (level>1) {
                subentityData.push_back(line);
            }
            if (contains(line.second, '}')) {
                level--;
                if (level==1) {
                    Entity* subentity = new Entity;
                    subentity->parseData(subentityData);
                    subentityData.clear();
                    lowerEntities.push(Pair<std::string, Entity>(subentityName, *subentity));
                }
            }
        }
    }
}
