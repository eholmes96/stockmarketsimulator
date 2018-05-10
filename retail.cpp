#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <string>

#include "company.h"
#include "retail.h"

using namespace std;

retail::retail()
{}

void retail::startSales()
{
    sales[0] = 0.8*company::getRev(0);
    for(int i = 1; i < 4; i++ )
    {
        sales[i] = company::getRev(i) * .8 + rand()%100;
    }
}

void retail::setSales()
{
    sales[0] = sales[1];
    sales[1] = sales[2];
    sales[2] = sales[3];
    sales[3] = company::getRev(3) * .8 + rand()%100;
}

int retail::getSales(int i)
{
    return sales[i];
}

void retail::startStock(double IPO)
{
    stock[0] = IPO;
    for(int i = 1; i < 4; i++)
    {
        stock[i] = stock[i-1] * stockChange();
    }
}

void retail::setStock()
{
    stock[0] = stock[1];
    stock[1] = stock[2];
    stock[2] = stock[3];
    stock[3] = stock[2] * stockChange();
}

double retail::stockChange()
{
    int pvar = company::getProfit(4) - company::getProfit(3);
    double uvar = getSales(3) - getSales(2);
    int var = getrand();


    if((pvar >0) && (uvar > 0))
    {

        if(var < 33)
            return 1.1;
        else if((var >=33) && (var <66))
            return 1.2;
        else if((var >= 66) && (var <100))
            return 1.3;
    }

    else if((pvar >0) ^ (uvar > 0))
    {
        if(var < 33)
            return 0.9;
        else if((var >=33) && (var <66))
            return 1.05;
        else if((var >= 66) && (var <100))
            return 1.1;
    }
    else if((pvar == 0) | (uvar == 0))
    {
        if(var < 33)
            return 0.9;
        else if((var >=33) && (var <66))
            return 0.95;
        else if((var >= 66) && (var <100))
            return 1.1;
    }
    else
    {
        if(var < 33)
            return 0.8;
        else if((var >=33) && (var <66))
            return 0.9;
        else if((var >= 66) && (var <100))
            return 0.95;
    }
}

double retail::getStock(int i)
{
    return stock[i];
}


void retail::print()
{
    company::print();
    cout << "SALES:" << setw(6);
    for(int i = 0; i < 4; i++)
    {
    cout << right << setprecision(3) <<retail::getSales(i) << setw(10);
    }
    cout << endl;

    cout << "PRICE: " << setw(6);
    for(int i = 0; i < 4; i++)
    {
    cout << right << setprecision(3) <<retail::getStock(i) << setw(10);
    }
    cout << endl;

}

