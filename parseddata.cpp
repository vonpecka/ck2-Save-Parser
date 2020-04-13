#include "parseddata.h"

namespace ck2
{
    void ParsedData::parse()
    {
        analyzePositions();
        extractDynasties();
        extractCharacters();
        extractLandedTitles();
    }


    // Get the amount of characters parsed
    unsigned int ParsedData::sizeOfCharacters() const
    {
        return characters.size();
    }

    // Get a character from an ID
    Character &ParsedData::getCharacter(unsigned int ID)
    {
        return *characters.at(ID);
    }

    // Get a landed title from an ID
    Title &ParsedData::getLandedTitle(std::string abbr)
    {
        return *titles.at(abbr);
    }

    void ParsedData::analyzePositions()
    {
        // Retreive critical line positions for the different categories
        for (int l = 0; l < file.getData().size(); l++)
        {
            std::string line = file.getData().at(l);

            if (line == "dynasties=" && key_lines.at(DYNASTY) == 0)
            {
                key_lines.at(DYNASTY) = l;
            }

            if (line == "character=" && key_lines.at(CHARACTERS) == 0)
            {
                key_lines.at(CHARACTERS) = l;
            }

            if (line == "provinces=" && key_lines.at(PROVINCES) == 0)
            {
                key_lines.at(PROVINCES) = l;
            }

            // it starts on line 883 986 in the test file Derby775_07_18.ck2
            if (line == "title=" && key_lines.at(DYNASTY) != 0 && key_lines.at(CHARACTERS) != 0 && key_lines.at(PROVINCES) != 0 && key_lines.at(TITLE) == 0)
            {
                key_lines.at(TITLE) = l;
            }
        }
    }

    void ParsedData::extractDynasties()
    {
        //Parse Dynasties
        std::vector<Pair<int, std::string>> data;
        int lastID = -1;
        int level = 1;
        for (int i = key_lines.at(DYNASTY) + 2; level > 0; i++)
        {
            std::string line(file.getData().at(i));

            // Check if the dynasty is done
            if (line.length() > 1 && line.at(line.length() - 1) == '=' && level == 1)
            {
                // If its the first person, you've got to pass the ID
                if (lastID == -1)
                    lastID = std::stoi(std::string(line.begin(), line.begin() + line.length() - 1));

                // If there is no data for some reason, dont add an object
                if (data.size() == 0) continue;

                Dynasty* dynasty = new Dynasty;
                dynasty->ID = lastID;
                dynasty->parseData(data);
                dynasties.push(Pair<int, Dynasty>(dynasty->ID, *dynasty));

                // Clear the data for the next character
                data.clear();

                // Begin ID for the next character
                lastID = std::stoi(std::string(line.begin(), line.begin() + line.length() - 1));

                continue;
            }

            // If the dynasty continues, determine whether or not to increment
            // or decrement the current level
            if (contains(line, '{')) level++;
            if (contains(line, '}')) level--;

            // Push the current line to the data
            data.push_back(Pair<int, std::string>(level, line));
        }
    }

    void ParsedData::extractCharacters()
    {
        // Parse Characters
        std::vector<Pair<int, std::string>> data;
        int lastID = -1;
        int level = 1;
        for (int i = key_lines.at(CHARACTERS) + 2; level > 0; i++)
        {
            std::string line(file.getData().at(i));

            // Check if the character is done
            if (line.length() > 1 && line.at(line.length() - 1) == '=' && level == 1)
            {
                // If its the first person, you've got to pass the ID
                if (lastID == -1)
                    lastID = std::stoi(std::string(line.begin(), line.begin() + line.length() - 1));

                // If there is no data for some reason, dont add an object
                if (data.size() == 0) continue;

                // Create the character
                Character* character = new Character;
                character->ID = lastID;
                character->parseData(data);

                // Lazy way of passing global data to the character class
                character->characterList = &characters;
                character->childList     = &children;
                character->dynastyList   = &dynasties;

                // Push the character
                characters.push(Pair<int, Character>(lastID, *character));

                // Determine if character has a mother
                if (character->dictionary.at("mot"))
                {
                    // Get the ID of the mother
                    int mother = std::stoi(*character->dictionary.at("mot"));

                    // If the mother isn't catalogued in the children list,
                    // make a new entry and pass this current character as one
                    // of their children
                    if (!children.at(mother))
                    {
                        children.push(
                            Pair<int, std::vector<Character*>>(
                                std::stoi(*character->dictionary.at("mot")),
                                { character }
                            )
                        );
                    }
                    // Otherwise, add this character to that person's children
                    else
                    {
                        children.at(std::stoi(*character->dictionary.at("mot")))->push_back(character);
                    }
                }

                // Determine if character has a father
                if (character->dictionary.at("fat"))
                {
                    // Get the ID of the father
                    int father = std::stoi(*character->dictionary.at("fat"));

                    // If the father isn't catalogued in the children list,
                    // make a new entry and pass this current character as one
                    // of their children
                    if (!children.at(father))
                    {
                        children.push(
                            Pair<int, std::vector<Character*>>(
                                std::stoi(*character->dictionary.at("fat")),
                                { character }
                            )
                        );
                    }
                    // Otherwise, add this character to that person's children
                    else
                    {
                        children.at(std::stoi(*character->dictionary.at("fat")))->push_back(character);
                    }
                }

                // Clear the data for the next character
                data.clear();

                // Begin ID for the next character
                lastID = std::stoi(std::string(line.begin(), line.begin() + line.length() - 1));

                continue;
            }

            // If the character continues, determine whether or not to increment
            // or decrement the current level
            if (contains(line, '{')) level++;
            if (contains(line, '}')) level--;

            // Push the current line to the data
            data.push_back(Pair<int, std::string>(level, line));
        }

    }

    void ParsedData::extractLandedTitles()
    {
        //Parse landed titles

        /*// Code to create mock object
        ck2::Title* d_gelre = new ck2::Title();
        d_gelre->dictionary.push(ck2::Pair<std::string, std::string>(std::string("holder"), std::string("6392")));
        d_gelre->dictionary.push(ck2::Pair<std::string, std::string>(std::string("liege"), std::string("k_france")));
        d_gelre->dictionary.push(ck2::Pair<std::string, std::string>(std::string("succession"), std::string("gavelkind")));
        d_gelre->dictionary.push(ck2::Pair<std::string, std::string>(std::string("gender"), std::string("agnatic")));
        titles.push(ck2::Pair<std::string, ck2::Title>(std::string("d_gelre"), *d_gelre));*/

        std::vector<Pair<int, std::string>> data;
        int lastID = 1;
        int level = 1;
        std::string abbr = "";
        for (int i = key_lines.at(TITLE) + 2; level > 0; i++)
        {
            std::string line(file.getData().at(i));

            // Check if the title is done
            if (line.length() > 1 && line.at(line.length() - 1) == '=' && level == 1)
            {
                // If its the first title, you've got to pass the ID
                if (lastID == 1)
                    abbr = std::string(line.begin(), line.begin() + line.length() - 1);

                // If there is no data for some reason, dont add an object
                if (data.size() == 0) continue;

                Title* title = new Title;
                title->ID = lastID;
                title->parseData(data);
                titles.push(Pair<std::string, Title>(abbr, *title));

                lastID++;
                // Clear the data for the next title
                data.clear();

                // Begin ID for the next character
                abbr = std::string(line.begin(), line.begin() + line.length() - 1);

                continue;
            }

            // If the title continues, determine whether or not to increment
            // or decrement the current level
            if (contains(line, '{')) level++;
            if (contains(line, '}')) level--;

            // Push the current line to the data
            data.push_back(Pair<int, std::string>(level, line));
        }


    }



}
