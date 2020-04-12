#include <texttools.h>
#include <entity.h>
#include <dynasties.h>

#ifndef CHARACTERS_H
#define CHARACTERS_H

namespace ck2
{
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
}

#endif // CHARACTERS_H
