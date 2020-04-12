#include "characters.h"

namespace ck2
{
Attributes::Attributes(std::string line)
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
unsigned int Attributes::diplomacy() const
{
    return _dip;
}

unsigned int Attributes::marshall() const
{
    return _mart;
}

unsigned int Attributes::stewardship() const
{
    return _stew;
}

unsigned int Attributes::intrigue() const
{
    return _int;
}

unsigned int Attributes::learning() const
{
    return _learn;
}

// Functions for getting data
std::string Character::name()
{
    return getStringfromDict("bn");
}

std::string Character::birthDate()
{
    return getStringfromDict("b_d");
}

std::string Character::deathDate()
{
    return getStringfromDict("d_d");
}

std::string Character::religion()
{
    return getStringfromDict("rel");
}

std::string Character::secret_religion()
{
    return getStringfromDict("secret_religion");
}

std::string Character::government()
{
    return getStringfromDict("gov");
}

std::string Character::title(bool formatted)
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

std::string Character::nickname(bool formatted)
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



Attributes Character::attributes()
{
    return Attributes(*dictionary.at("att"));
}

float Character::health()
{
    return getFloatFromDict("health");
}

float Character::fertility()
{
    return getFloatFromDict("fer");
}

float Character::wealth()
{
    return getFloatFromDict("wealth");
}

float Character::piety()
{
    return getFloatFromDict("piety");
}

float Character::prestige()
{
    return getFloatFromDict("prs");
}

Character* Character::lover()
{
    return getFromCharacterList("lover");
}

Character* Character::father()
{
    return getFromCharacterList("fat");
}

Character* Character::mother()
{
    return getFromCharacterList("mot");
}

Character* Character::spouse()
{
    return getFromCharacterList("spouse");
}

Character* Character::host()
{
    return getFromCharacterList("host");
}

Dynasty* Character::dynasty()
{
    std::string d_str = getStringfromDict("dnt");
    if (d_str == "") return nullptr;

    return dynastyList->at(std::stoi(d_str));
}

std::vector<Character*> Character::children()
{
    try {
        return *childList->at(ID);
    }
    catch (...)
    {
        return {};
    }
}

Character* Character::getFromCharacterList(std::string key)
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

}
