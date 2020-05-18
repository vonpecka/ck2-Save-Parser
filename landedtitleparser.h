#include <entity.h>

#ifndef LANDEDTITLEPARSER_H
#define LANDEDTITLEPARSER_H

namespace ck2
{

class LandedTitle : public Entity
{
    friend class LandedTitleParser;
    std::string name;
    std::string liege;
//    LandedTitle *deJureLiege;
//    Dictionary<std::string, *LandedTitle> deJureVassals;
    LandedTitle();
    LandedTitle(Entity source, std::string newName, std::string liegeName);
};


class LandedTitleParser : Parser
{
    Dictionary<std::string, LandedTitle> titles;
public:
    LandedTitleParser(const char* directory = "landed_titles.txt");
};

}
#endif // LANDEDTITLEPARSER_H
