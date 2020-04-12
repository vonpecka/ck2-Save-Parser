#include <datafile.h>
#include <texttools.h>
#include <parser.h>

#ifndef TRAITS_H
#define TRAITS_H

namespace ck2
{

//
// Object representing a trait
//
struct Trait
{
    Trait(unsigned int i, std::string n) :
        _name(n), _id(i)
    {

    }

    std::string name() const { return _name; }
    unsigned int id()  const { return _id; }

private:
    std::string _name;
    unsigned int _id;
};

//
// Object that handles Traits csv
//
class TraitCSV : public DataFile
{

public:
    TraitCSV(std::string dir) : DataFile(dir.c_str())
    {
        if (getData().size() == 0)
            throw std::runtime_error("traits.csv not found!");
    }
};

}

#endif // TRAITS_H
