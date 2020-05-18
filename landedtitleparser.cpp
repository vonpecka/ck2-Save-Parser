#include "landedtitleparser.h"
#include <datafile.h>


#include <qstring.h>
#include <qdebug.h>
namespace ck2
{
LandedTitle::LandedTitle()
{

}

LandedTitle::LandedTitle(Entity source, std::string newName, std::string liegeTitle)
{

    std::vector<Pair<int, std::string>> data;
    for (int lineNumber = 0; lineNumber < source.dictionary.size(); lineNumber++) {
        std::string line = source.dictionary.number(lineNumber).second;
        data.push_back(Pair<int, std::string>(lineNumber,line));
    }
    parseData(data);
    name = newName;

    for (int i = 0; i < source.lowerEntities.size(); i++) {
        lowerEntities.push(source.lowerEntities.number(i));
    }
    liege = liegeTitle;

}

LandedTitleParser::LandedTitleParser(const char* directory)
{
    DataFile landedTitlesFile(directory);
    std::string name;
    std::vector<Pair<int, std::string>> data;

    int level = 1;
    int lineNumber = 0;
    for (int i = 0; i < landedTitlesFile.getData().size(); i++)
    {
        std::string line(landedTitlesFile.getData().at(i));
        lineNumber++;

        if (contains(line, '{')) {
            if (level==1) {
                name = getProperty(line).first;
                name = remove(name,' ');
            }
            level++;
        }

        data.push_back(Pair<int, std::string>(lineNumber,line));

        if (contains(line, '}')) {
            level--;
            if (level==1) {
                LandedTitle* landedTitle = new LandedTitle;
                landedTitle->name = name;
                landedTitle->parseData(data);
                data.clear();
                lineNumber = 0;
                titles.push(Pair<std::string, LandedTitle>(name, *landedTitle));

            }
        }
    }
    int i = 0;
    while (i < titles.size())
    {        
        for (int j = 0; j < titles.number(i).second.lowerEntities.size(); j++ ) {
            std::string lowerEntityName = titles.number(i).second.lowerEntities.number(j).first;
            if (lowerEntityName.size()>1) {
                if (lowerEntityName.at(1)=='_') {
                    LandedTitle* vassalTitle = new LandedTitle(titles.number(i).second.lowerEntities.number(j).second, lowerEntityName, titles.number(i).first);
                    titles.push(Pair<std::string, LandedTitle>(lowerEntityName, *vassalTitle));

                }
            }
        }
        i++;
    }
}

}
