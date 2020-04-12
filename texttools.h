#include <string>
#include <vector>

#ifndef TEXTTOOLS_H
#define TEXTTOOLS_H


namespace ck2
{
    // Strip a given character from the beginning and ends
    // of a string
    std::string strip(const std::string &str, char c);

    // Splits a string into a vector with a given delimeter
    std::vector<std::string> split(const std::string &str, char del);

    // Combiles a vector into a string with a given delimeter
    std::string combine(std::vector<std::string> v, char glue);
}


#endif // TEXTTOOLS_H
