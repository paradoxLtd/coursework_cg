#ifndef INDEXEX_H
#define INDEXEX_H

#include <vector>
class Indexes
{
    public:
        std::vector<int> ind;

        std::vector<int>::size_type size() const;

        void clear();

        int &operator[](const int index);

        int operator[](const int index) const;

        Indexes();

        Indexes(const Indexes &indexes);

        Indexes(Indexes &&indexes);

        Indexes& operator=(const Indexes& indexes);

        Indexes& operator=(Indexes&& indexes);

};

#endif // INDEXEX_H
