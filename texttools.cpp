#include "texttools.h"

namespace ck2
{
    // Strip a given character from the beginning and ends
    // of a string
    std::string strip(const std::string &str, char c)
    {
        unsigned int first, last;
        for (int i = 0; i < str.length(); i++)
            if (str[i] != c)
            {
                first = i; break;
            }

        for (int i = str.length(); i > -1; i--)
        {
            if (str[i] != c)
            {
                last = i; break;
            }
        }

        if (first > last) return std::string();

        return std::string(str.begin() + first, str.begin() + last);
    }

    // Splits a string into a vector with a given delimeter
    std::vector<std::string> split(const std::string &str, char del)
    {
        std::vector<std::string> r;

        unsigned int last = 0;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == del)
            {
                r.push_back(std::string(str.begin() + last, str.begin() + i));
                last = i;
            }
            if (i == str.length() - 1)
            {
                int offset = 1;
                if (r.size() == 0) offset = 0;

                r.push_back(std::string(str.begin() + last + offset, str.end()));
                break;
            }
        }

        return r;
    }

    // Combiles a vector into a string with a given delimeter
    std::string combine(std::vector<std::string> v, char glue)
    {
        std::string r;

        for (int i = 0; i < v.size(); i++)
            r += v.at(i) + glue;

        return r;
    }

}
