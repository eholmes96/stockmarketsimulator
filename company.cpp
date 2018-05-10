
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "company.h"
using namespace std;

int getrand()
{
    int randnum = rand() % 100 ;
    return randnum;
}

company::company()
{

}

void company::setRevenues(int seed)
{
    revenue[0] = revenue[1];
    revenue[1] = revenue[2];
    revenue[2] = revenue[3];
    revenue[3] = revenue[2] * company::randConst(revenue[2], seed);

}

void company::startRevenue(int seed)
{
    revenue[0] = 1000*seed;
    for(int i = 1; i < 4; i++)
    {
        revenue[i] = revenue[i-1] * company::randConst(revenue[i-1], seed);
    }
}

int company::getRev(int i)
{
  return revenue[i];
}



void company::setCosts(int seed)
{
    costs[0] = costs[1];
    costs[1] = costs[2];
    costs[2] = costs[3];
    costs[3] = (costs[3] * company::randConst(revenue[2], seed));

}

void company::startCosts(int seed)
{
    costs[0] = revenue[0] * 0.8;
    for(int i = 1; i < 4; i++)
    {
        costs[i] = (costs[i-1] * company::randConst(costs[i-1], seed));
    }
}

int company::getCosts(int i)
{
    return costs[i];
}


void company::setProfit()
{
    profit[0] = profit[1];
    profit[1] = profit[2];
    profit[2] = profit[3];
    profit[3] = revenue[3] - costs[3];
}

void company::startProfit()
{
    for(int i = 0; i < 4; i++)
    {
        profit[i] = revenue[i] - costs[i];
    }
}

int company::getProfit(int i)
{
    return profit[i];
}


float company::randConst(int big, int seed)
{

    int var = getrand(); //return a number between 1 and 100
    float perf = .01*big/seed; //how much better the company has done
        if (var <= 5)
            return 0.6;
        else if((var <= 15) && (var > 6))
            return 0.8;
        else if((var <= 30) && (var > 15))
        {
            if (perf > 1.3)
                return .95;
            else if ((perf > 1.1) && (perf >= 1.3))
                return 0.9;
            else if ((perf > 0.9) && (perf >= 1.1))
                return 0.85;
            else if (perf < 0.9)
                return 0.8;
        }
        else if((var <= 50) && (var > 30))
        {
            if (perf > 1.3)
                return 1.05;
            else if ((perf > 1.1) && (perf >= 1.3))
                return 1.0;
            else if ((perf > 0.9) && (perf >= 1.1))
                return 0.95;
             else if (perf < 0.9)
                return 0.9;
        }
        else if((var <= 70) && (var > 50))
        {
            if (perf > 1.3)
                return 1.1;
            else if ((perf > 1.1) && (perf >= 1.3))
                return 1.05;
            else if ((perf > 0.9) && (perf >= 1.1))
                return 1;if (var <= 5)
            return 0.6;
        else if((var <= 15) && (var > 6))
            return 0.8;
             else if (perf < 0.9)
                return 0.95;
        }
         else if((var <= 85) && (var > 70))
        {
            if (perf > 1.3)
                return 1.2;
            else if ((perf > 1.1) && (perf >= 1.3))
                return 1.15;
            else if ((perf > 0.9) && (perf >= 1.1))
                return 1.1;
            else if (perf < 0.9)
                return 1.05;
        }
        else if((var <= 95) && (var > 85))
            return 1.2;
        else if (var > 95)
            return 1.4;
        else
            return 1.45;

}


void company::print()
{
    cout << setw(15) << right << "Q1" << setw(10) << "Q2" << setw(10)
        << "Q3" << setw(10) << "Q4" << setw(10)
        << endl;

    cout << "REVENUES: " << setw(6);
    for(int i = 0; i < 4; i++){
        cout << right <<company::getRev(i) << setw(10);
    }
    cout << endl;

    cout << "COSTS: " << setw(6);
    for(int i = 0; i < 4; i++){
        cout << right <<company::getCosts(i) << setw(10);
    }
    cout << endl;

    cout << "PROFIT:" << setw(6);
    for(int i = 0; i < 4; i++)
    {
    cout << right <<company::getProfit(i) << setw(10);
    }
    cout << endl;

}
