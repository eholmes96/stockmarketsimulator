#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <string>

#include "company.h"
#include "tech.h"

using namespace std;

tech::tech()
{}

void tech::startUsers(int seed)
{
    users[0] = seed;
    for(int i = 1; i < 4; i++)
    {
        users[i] = users[i-1] * usergrowth(users[i-1]);

    }
}

void tech::setUsers()
{
    users[0] = users[1];
    users[1] = users[2];
    users[2] = users[3];
    users[3] = users[3] * usergrowth(users[3]);
}

double tech::getUsers(int i)
{
    return users[i];
}

double tech::usergrowth(int last)
{
    int rev4 = company::getRev(4);
    int rev3 = company::getRev(3);
    int var = getrand();
    if ( rev4 > rev3 )
    {
        if(var < 33)
            return 1.1;
        else if((var >=33) && (var <66))
            return 1.2;
        else if((var >= 66) && (var <100))
            return 1.3;
    }
    else if (rev4 == rev3)
    {
        if(var < 33)
            return 0.9;
        else if((var >=33) && (var <66))
            return 1;
        else if((var >= 66) && (var <100))
            return 1.1;
    }
    else if (rev4< rev3)
    {
        if(var < 33)
            return 0.7;
        else if((var >=33) && (var <66))
            return 0.8;
        else if((var >= 66) && (var <100))
            return 0.9;
    }

}

void tech::startStock(double IPO)
{
    stock[0] = IPO;
    for(int i = 1; i < 4; i++)
    {
        stock[i] = stock[i-1] * stockChange();
    }
}

void tech::setStock()
{
    stock[0] = stock[1];
    stock[1] = stock[2];
    stock[2] = stock[3];
    stock[3] = stock[2] * stockChange();
}

double tech::stockChange()
{
    int pvar = company::getProfit(4) - company::getProfit(3);
    double uvar = getUsers(4) - getUsers(3);
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

double tech::getStock(int i)
{
    return stock[i];
}

void tech::print()
{
    company::print();
    cout << "USERS:" << setw(6);
    for(int i = 0; i < 4; i++)
    {
    cout << right << setprecision(3) <<tech::getUsers(i) << setw(10);
    }
    cout << endl;
    cout << "(in millions)" << endl;

    cout << "PRICE: " << setw(6);
    for(int i = 0; i < 4; i++)
    {
    cout << right << setprecision(3) <<tech::getStock(i) << setw(10);
    }
    cout << endl;



}

