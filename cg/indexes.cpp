#include "Indexes.h"

std::vector<int>::size_type Indexes::size() const
{
    return ind.size();
}

void Indexes::clear()
{
    ind.clear();
}

int &Indexes::operator[](const int index)
{
    return ind[index];
}

int Indexes::operator[](const int index) const
{
    return ind[index];
}

Indexes::Indexes()
{

}

Indexes::Indexes(const Indexes &indexes)
{
    clear();
    for (auto i = 0; i < size(); i++)
    {
        ind[i] = indexes[i];
    }
}

Indexes::Indexes(Indexes &&indexes)
{
    int s = size();
    clear();
    for (int i = 0; i < s; i++)
    {
        ind[i] = indexes[i];
    }
}
Indexes& Indexes::operator=(const Indexes& indexes)
{
    int s = size();
    clear();
    for (int i = 0; i < s; i++)
    {
        ind[i] = indexes[i];
    }
    return *this;
}

Indexes& Indexes::operator=(Indexes&& indexes)
{
    {
        int s = size();
        clear();
        for (int i = 0; i < s; i++)
        {
            ind[i] = indexes[i];
        }
    }
    return *this;
}
