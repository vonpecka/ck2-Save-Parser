/*****************************
*	Author: Max Ortner
*	Date:   March 10, 2019
*/

#pragma once

#ifndef CK2_NO_STDLIB
    #include <texttools.h>
    #include <datafile.h>
    #include <parser.h>
    #include <entity.h>
    #include <dynasties.h>
    #include <characters.h>
#endif

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

		void parse()
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

				if (line == "title=" && key_lines.at(DYNASTY) != 0 && key_lines.at(CHARACTERS) != 0 && key_lines.at(PROVINCES) != 0 && key_lines.at(TITLE) == 0)
				{
					key_lines.at(TITLE) = l;
				}
			}

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

			// Parse Characters
			data.clear();
			lastID = -1;
			level = 1;
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

	public:
		// Initialize variables and parse the data
        ParsedData(DataFile f) :
			file(f), key_lines(AMOUNT)
		{
			parse();
		}

		// Get the amount of characters parsed
		unsigned int sizeOfCharacters() const 
		{
			return characters.size();
		}

		// Get a character from an ID
		Character &getCharacter(unsigned int ID)
		{
			return *characters.at(ID);
		}
	};
}
