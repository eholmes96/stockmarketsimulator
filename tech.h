#ifndef TECH_H_INCLUDED
#define TECH_H_INCLUDED
#include "company.h"
#include <iostream>
#include <cstdlib>

 using namespace std;

class tech : public company
{
public:
    tech();

    void startUsers(int);
    void setUsers();
    double getUsers(int);
    double usergrowth(int);

    void startStock(double);
    void setStock();
    double getStock(int);
    double stockChange();


    virtual void print();

private:
    double users[4];
    double stock[4];
};


#endif // TECH_H_INCLUDED
