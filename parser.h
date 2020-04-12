#include <abstracts.h>


#ifndef PARSER_H
#define PARSER_H

namespace ck2
{
    //
    // Base class of functions for parsing data
    //
    class Parser
    {
    protected:

        // Returns Pair of strings given a string of a property
        StringPair getProperty(std::string line, char del = '=') const;

        // Determines whether or not a given character is in a given string
        bool contains(std::string line, char c) const;

        // Replaces all occurences of one character with another
        std::string replace(std::string line, char c, char rep) const;

        // Removes all occurrences of a character
        std::string remove(std::string line, char c) const;
    };
}

#endif // PARSER_H
