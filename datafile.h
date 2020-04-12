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
        DataFile(const char* directory);
        std::vector<std::string> &getData();
    };
}

#endif // DATAFILE_H
