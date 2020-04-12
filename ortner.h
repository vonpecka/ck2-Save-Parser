/*****************************
*	Author: Max Ortner
*	Date:   March 10, 2019
*/

#pragma once

#ifndef CK2_NO_STDLIB
	#include <fstream>
	#include <string>
	#include <vector>
    #include <iostream>
    #include <abstracts.h>
    #include <texttools.h>
    #include <datafile.h>
#endif

namespace ck2
{
	//
	// Base class of functions for parsing data
	//
	class Parser
	{
	protected:
		typedef Pair<std::string, std::string> StringPair;

		// Returns Pair of strings given a string of a property
		StringPair getProperty(std::string line, char del = '=') const
		{
			StringPair r;

			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] != del) continue;

				r.first  = std::string(line.begin(), line.begin() + i);
				r.second = std::string(line.begin() + i + 1, line.end());

				break;
			}

			return r;
		}

		// Determines whether or not a given character is in a given string
		bool contains(std::string line, char c) const
		{
			for (int i = 0; i < line.length(); i++)
				if (line[i] == c)
					return true;

			return false;
		}

		// Replaces all occurences of one character with another
		std::string replace(std::string line, char c, char rep) const
		{
			std::string r;

			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] != c)
					r += line[i];
				else
					r += rep;
			}

			return r;
		}

		// Removes all occurrences of a character
		std::string remove(std::string line, char c) const
		{
			std::string r;

			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] != c)
					r += line[i];
			}

			return r;
		}
	};

	//
	// Object representing a trait
	//
	struct Trait
	{
		Trait(unsigned int i, std::string n) :
			_name(n), _id(i)
		{

		}

		std::string name() const { return _name; }
		unsigned int id()  const { return _id; }

	private:
		std::string _name;
		unsigned int _id;
	};

	//
	// Object that handles Traits csv
	//
    class TraitCSV : public DataFile
	{

	public:
		TraitCSV(std::string dir) :
            DataFile(dir.c_str())
		{
			if (getData().size() == 0)
				throw std::runtime_error("traits.csv not found!");
		}
	};

	TraitCSV traitCSV("traits.csv");

	struct Attributes : Parser
	{
		Attributes(std::string line)
		{
			// Clean up the string from the dictionary
			std::string str_attr;
			str_attr = remove(line, '}');
			str_attr = remove(str_attr, '{');

			// Delimit the string with spaces
			std::vector<std::string> ts = split(str_attr, ' ');

			// Clean up each object
			for (std::string &str : ts)
				str = strip(str, ' ');

			for (int i = 0; i < 5 && i < ts.size(); i++)
				_vals[i] = std::stoi(ts.at(i));
		}

		// Getting the values
		unsigned int diplomacy() const
		{
			return _dip;
		}

		unsigned int marshall() const 
		{
			return _mart;
		}

		unsigned int stewardship() const
		{
			return _stew;
		}

		unsigned int intrigue() const
		{
			return _int;
		}

		unsigned int learning() const
		{
			return _learn;
		}

	private:
		union 
		{
			struct
			{
				unsigned int _vals[5];
			};

			struct 
			{
				unsigned int _dip, _mart, _stew, _int, _learn;
			};
		};
	};

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

	//
	// Object representing a Title
	//
	struct Title : public Entity
	{
        friend class ParsedData;

		std::string succession()
		{
			return getStringfromDict("succession");
		}

		std::string gender()
		{
			return getStringfromDict("gender");
		}

		unsigned int holderID()
		{
			return (int)getFloatFromDict("holder");
		}
	};

	//
	// Object representing a Dynasty
	//
	struct Dynasty : public Entity
	{
        friend class ParsedData;

		std::string name()
		{
			return getStringfromDict("name");
		}

		std::string culture()
		{
			return getStringfromDict("culture");
		}

		std::string religion()
		{
			return getStringfromDict("religion");
		}
	};

	//
	// Object representing a Character
	//
	struct Character : public Entity
	{
        friend class ParsedData;

		// Functions for getting data
		std::string name()
		{
			return getStringfromDict("bn");
		}

		std::string birthDate()
		{
			return getStringfromDict("b_d");
		}

		std::string deathDate()
		{
			return getStringfromDict("d_d");
		}

		std::string religion()
		{
			return getStringfromDict("rel");
		}

		std::string secret_religion()
		{
			return getStringfromDict("secret_religion");
		}

		std::string government()
		{
			return getStringfromDict("gov");
		}

		std::string title(bool formatted = true)
		{
			std::string title = getStringfromDict("title");

			if (formatted && title.length() > 0)
			{
				title = std::string(title.begin() + 6, title.end());
				title = strip(title, '\t');

				auto title_split = split(title, '_');

				for (std::string &str : title_split)
					str[0] = toupper(str[0]);

				title = combine(title_split, ' ');

				return title;
			}

			return title;
		}

		std::string nickname(bool formatted = true)
		{
			std::string nickname = getStringfromDict("nick");

			if (formatted && nickname.length() > 0)
			{
				nickname = std::string(nickname.begin() + 5, nickname.end());
				nickname = strip(nickname, '\t');

				auto title_split = split(nickname, '_');

				for (std::string &str : title_split)
					str[0] = toupper(str[0]);

				nickname = combine(title_split, ' ');

				return nickname;
			}

			return nickname;
		}

		std::vector<Trait> traits()
		{
			std::vector<Trait> r;

			// Clean up the string from the dictionary
			std::string str_traits; 
			str_traits = remove(getStringfromDict("traits"), '}');
			str_traits = remove(str_traits, '{');
			str_traits = strip(str_traits, ' ');

			// Delimit the string with spaces
			std::vector<std::string> ts = split(str_traits, ' ');

			// Clean up each object
			for (std::string &str : ts)
				str = strip(str, ' ');

			// Go through each line of the csv
			for (int t = 0; t < traitCSV.getData().size(); t++)
				for (int i = 0; i < ts.size(); i++)
				{
					auto trait = getProperty(traitCSV.getData().at(t), ',');
					if (trait.second == ts.at(i))
					{
						r.push_back(Trait(std::stoi(trait.second), trait.first));
						continue;
					}
				}

			return r;
		}

		Attributes attributes()
		{
			return Attributes(*dictionary.at("att"));
		}

		float health()
		{
			return getFloatFromDict("health");
		}

		float fertility()
		{
			return getFloatFromDict("fer");
		}

		float wealth()
		{
			return getFloatFromDict("wealth");
		}

		float piety()
		{
			return getFloatFromDict("piety");
		}

		float prestige()
		{
			return getFloatFromDict("prs");
		}

		Character* lover()
		{
			return getFromCharacterList("lover");
		}
		
		Character* father()
		{
			return getFromCharacterList("fat");
		}

		Character* mother()
		{
			return getFromCharacterList("mot");
		}

		Character* spouse()
		{
			return getFromCharacterList("spouse");
		}

		Character* host()
		{
			return getFromCharacterList("host");
		}

		Dynasty* dynasty()
		{
			std::string d_str = getStringfromDict("dnt");
			if (d_str == "") return nullptr;

			return dynastyList->at(std::stoi(d_str));
		}

		std::vector<Character*> children()
		{
			try {
				return *childList->at(ID);
			}
			catch (...)
			{
				return {};
			}
		}

	private:
		Character* getFromCharacterList(std::string key)
		{
			try
			{
				if (!dictionary.at(key)) return nullptr;
				int id = std::stoi(*dictionary.at(key));
				return characterList->at(id);
			}
			catch (...)
			{
				return nullptr;
			}
		}

		Dictionary<int, Character>* characterList;
		Dictionary<int, std::vector<Character*>>* childList;
		Dictionary<int, Dynasty>* dynastyList;
	};

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
