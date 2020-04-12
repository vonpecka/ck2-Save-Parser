#include "datafile.h"

namespace ck2
{
DataFile::DataFile(const char* directory)
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

std::vector<std::string> &DataFile::getData()
{
    return data;
}



}
