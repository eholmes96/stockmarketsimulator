#ifndef COMPANY_H_INCLUDED
#define COMPANY_H_INCLUDED

class company
{
public:
    company();
    void setRevenues(int);
    void startRevenue(int);
    int getRev(int);

    void setCosts(int);
    void startCosts(int);
    int getCosts(int);

    void setProfit();
    void startProfit();
    int getProfit(int);

    float randConst(int, int);
    virtual void print();


private:
    int profit[4];
    int revenue[4];
    int costs[4];


};

int getrand();

#endif // COMPANY_H_INCLUDED
