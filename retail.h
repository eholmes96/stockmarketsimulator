#ifndef RETAIL_H_INCLUDED
#define RETAIL_H_INCLUDED

#include "company.h"
#include <iostream>
#include <cstdlib>

 using namespace std;

class retail : public company
{
public:
    retail();

    void startSales();
    void setSales();
    int getSales(int);

    void startStock(double);
    void setStock();
    double getStock(int);
    double stockChange();

    virtual void print();


private:
    double sales[4];
    double stock[4];

};

#endif // RETAIL_H_INCLUDED
