#include <texttools.h>
#include <datafile.h>
#include <parser.h>
#include <entity.h>
#include <dynasties.h>
#include <characters.h>

#ifndef PARSEDDATA_H
#define PARSEDDATA_H


namespace ck2
{
    //
    // Object that creates all data for the save file
    //
    class ParsedData : Parser
    {
        DataFile &file;
        Dictionary<int, Character> characters;
        Dictionary<int, Dynasty>   dynasties;

        //Dictionary<int, std::vector<Title>> titles;

        Dictionary<int, std::vector<Character*>> children;

        typedef enum {
            DYNASTY,
            CHARACTERS,
            PROVINCES,
            TITLE,
            AMOUNT
        } LINES;

        std::vector<int> key_lines;

        void parse();

    public:
        // Initialize variables and parse the data
        ParsedData(DataFile f) :
            file(f), key_lines(AMOUNT)
        {
            parse();
        }

        // Get the amount of characters parsed
        unsigned int sizeOfCharacters() const;

        // Get a character from an ID
        Character &getCharacter(unsigned int ID);

    private:
        void analyzePositions();
        void extractDynasties();
        void extractCharacters();

    };
}

#endif // PARSEDDATA_H
