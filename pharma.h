#ifndef PHARMA_H_INCLUDED
#define PHARMA_H_INCLUDED



class pharma : public company
{
public:
    pharma();

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

#endif // PHARMA_H_INCLUDED
