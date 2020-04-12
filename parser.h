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
}

#endif // PARSER_H
