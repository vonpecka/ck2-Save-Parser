#include <vector>
#include <string>

#ifndef ABSTRACTS_H
#define ABSTRACTS_H
namespace ck2
{

//
// Pair of two objects of type F and S
//
template<typename F, typename S>
struct Pair
{
    F first;
    S second;

    Pair()
    {

    }

    Pair(F f, S s) :
        first(f), second(s)
    {

    }
};

//
// A List of Pairs
//
template<typename F, typename S>
struct Dictionary
{
    virtual S* at(F val)
    {
        for (int i = 0; i < data.size(); i++)
            if (val == data.at(i).first)
                return &data.at(i).second;

        return nullptr;
    }

    virtual void push(const Pair<F, S> &val)
    {
        data.push_back(val);
    }

    virtual unsigned int size() const
    {
        return data.size();
    }

protected:
    std::vector< Pair<F, S> > data;
};

typedef Pair<std::string, std::string> StringPair;


}
#endif // ABSTRACTS_H
