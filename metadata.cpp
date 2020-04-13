#include "metadata.h"

namespace ck2
{


    std::string Metadata::getSavedDate()
    {
        return getStringfromDict("date");
    }

    std::string Metadata::getVersion()
    {
        return getStringfromDict("version");
    }

    Metadata::Metadata(DataFile f)
    {
        std::vector<Pair<int, std::string>> data;
        data.push_back(Pair<int, std::string>(1, f.getData().at(1)));
        data.push_back(Pair<int, std::string>(2, f.getData().at(2)));
        parseData(data);
    }

}
