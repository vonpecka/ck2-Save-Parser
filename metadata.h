#include <entity.h>
#include <datafile.h>

#ifndef METADATA_H
#define METADATA_H

namespace ck2
{

struct Metadata : public Entity
{
    Metadata(DataFile f);
    public:
        std::string getSavedDate();
        std::string getVersion();

};

}

#endif // METADATA_H
