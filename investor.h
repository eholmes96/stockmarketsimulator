#ifndef INVESTOR_H_INCLUDED
#define INVESTOR_H_INCLUDED



struct investorRecord {
    int ID;
    char name[15];
    int shares[5] = {0};
    double cash;
};

class investor

{

public:
      explicit investor(const char* );
      ~investor();

      void createData(int);
      void invest();
      void displayData();
      void clearStream();
      void writeFile();
      void playerStats(int);
      void buy(int, int, int, double);
      void sell(int, int, int, double);
        //stock num, ID, amt, price
      int getShares(int, int);
        //stock num, ID
      double getCash(int);
      void callName(int);

private:
    investorRecord investorData;
    std::fstream investorFile;

};



#endif // INVESTOR_H_INCLUDED
