#include <texttools.h>
#include <entity.h>
#include <dynasties.h>

#ifndef CHARACTERS_H
#define CHARACTERS_H

namespace ck2
{
    class Attributes : Parser
    {
    public:
        Attributes(std::string line);

        // Getting the values
        unsigned int diplomacy() const;
        unsigned int marshall() const;
        unsigned int stewardship() const;
        unsigned int intrigue() const;
        unsigned int learning() const;

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
        std::string name();
        std::string birthDate();
        std::string deathDate();
        std::string religion();
        std::string secret_religion();
        std::string government();
        std::string title(bool formatted = true);
        std::string nickname(bool formatted = true);
        Attributes attributes();
        float health();
        float fertility();
        float wealth();
        float piety();
        float prestige();
        Character* lover();
        Character* father();
        Character* mother();
        Character* spouse();
        Character* host();
        Dynasty* dynasty();
        std::vector<Character*> children();

    private:
        Character* getFromCharacterList(std::string key);
        Dictionary<int, Character>* characterList;
        Dictionary<int, std::vector<Character*>>* childList;
        Dictionary<int, Dynasty>* dynastyList;
    };
}

#endif // CHARACTERS_H
