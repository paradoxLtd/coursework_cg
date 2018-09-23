#ifndef INDEXEX_H
#define INDEXEX_H

#include <vector>
#include <iostream>

// ОЧЕНЬ ВАЖНО: OBJ начинает отчёт не с нуля, а с единицы
// из за этого индексы хранят значения на 1 больше настоящих
// Если будет необходимо вручную создать объект Indexes
// например с первыми тремя вершинами, то вместо Indexes
// indexes(0,1,2), пишите indexes(1,2,3) - отсчёт с единицы.
class Indexes
{
public:
    std::vector<int> ind;

        std::vector<int>::size_type size() const;

        void clear();

        void push(int index);

        int &operator[](const int index);

        int operator[](const int index) const;

        Indexes();

        Indexes(int a, int b, int c);

        Indexes(const Indexes &indexes);

        Indexes(Indexes &&indexes);

        Indexes& operator=(const Indexes& indexes);

        Indexes& operator=(Indexes&& indexes);

        bool isEqual(const Indexes &B)noexcept;

        bool operator==(const Indexes &B)noexcept;

        bool operator!=(const Indexes &B)noexcept;

        friend std::ostream& operator<<(std::ostream& os,
                                        const Indexes& in);

};

#endif // INDEXEX_H
