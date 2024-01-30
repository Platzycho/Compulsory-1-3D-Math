#include "Task_1.h"
#include <iostream>
#include <algorithm>


double Task_1::taskOneFunction(double x1, double x2, double x3, double x4, double xValue)
{
    double numOne = x1;
    double numTwo= x2;
    double numThree = x3;
    double numFour = x4;
    double numX = xValue;

    double function = x1 * pow(xValue, 4) + x2 * pow(xValue, 2) + x3 * xValue + x4;

    std::cout << "f(" << numX << ") =" << function << std::endl;

    return 0.0;
}
