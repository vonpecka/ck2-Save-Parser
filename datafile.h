#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <texttools.h>

#ifndef DATAFILE_H
#define DATAFILE_H


namespace ck2
{
    //
    // File object for reading files at a given directory
    //
    class DataFile
    {
        // Stores each line
        std::vector<std::string> data;

        // Key Characters to strip out of each line
        std::vector<char> key_chars = {
            ' ', '\t'
        };

    public:
        DataFile(const char* directory)
        {
            std::fstream stream(directory, std::ios::in);

            if (!stream)
                throw std::runtime_error(std::string("Cannot open file ") + directory);

            for (std::string line; std::getline(stream, line);)
            {
                for (int c = 0; c < key_chars.size(); c++)
                    line = strip(line, key_chars.at(c));

                data.push_back(line);
            }

            stream.close();
        }

        std::vector<std::string> &getData()
        {
            return data;
        }
    };
}

#endif // DATAFILE_H
