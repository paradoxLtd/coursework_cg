#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <cmath>

//point
class Debug
{
public:
    static void message(char* text1, char *text2,
            double i_wait, double i_get)
    {
        std::cout <<"\n" << text1 << "Ожидаемый результат:" <<
                    i_wait << ". Получили:" << i_get;
    }

    static bool compare(double a, double b)
    {
        double eps = 0.0001;
        return (fabs(b - a) > eps);
    }

};

#endif // DEBUG_H
