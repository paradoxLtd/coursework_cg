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

// ОЧЕНЬ ВАЖНО: OBJ начинает отчёт не с нуля, а с единицы
// из за этого индексы хранят значения на 1 больше настоящих
// поэтому для корректной работы возвращаем index - 1


int Indexes::operator[](const int index) const
{
    return (ind[index] - 1);
}

void Indexes::push(int index)
{
    ind.push_back(index);
}


Indexes::Indexes()
{

}

Indexes::Indexes(int a, int b, int c)
{
    ind.push_back(a);
    ind.push_back(b);
    ind.push_back(c);
}


Indexes::Indexes(const Indexes &indexes)
{
    this->ind = indexes.ind;
}

Indexes::Indexes(Indexes &&indexes)
{
    this->ind = indexes.ind;
}
Indexes& Indexes::operator=(const Indexes& indexes)
{
    this->ind = indexes.ind;
    return *this;
}

Indexes& Indexes::operator=(Indexes&& indexes)
{
    this->ind = indexes.ind;
    indexes.clear();
    return *this;
}

//https://stackoverflow.com/questions/6248044/c-comparing-two-vectors/6248053#6248053
bool Indexes::isEqual(const Indexes &B)noexcept
{
    return(ind == B.ind);
}

bool Indexes::operator==(const Indexes& other)noexcept
{
    return isEqual(other);
}

bool Indexes::operator!=(const Indexes& other)noexcept
{
    return !isEqual(other);
}


std::ostream& operator<<(std::ostream& os,
                                const Indexes& in)
{
   int s = in.size();
   os << "\n Indexes: size: " << s << ",consists of:";
   for (int index: in.ind)
   {
         os << " " << index << ",";
   }

   return os;
}

