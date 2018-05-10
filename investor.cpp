
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include "company.h"
#include "investor.h"

using namespace std; 

investor::investor(const char *filename)
{
    investorFile.open(filename, ios::in | ios::out | ios::binary);

    if(!investorFile)
    {
        investorFile.open(filename, ios::out );
        investorFile.close();
        investorFile.open(filename, ios::in | ios::out | ios::binary);

        if (investorFile) {
            investorData.ID = 0;
            investorData.name[0] = '\0';
            investorData.shares[0] = '\0';
            investorData.cash = 0.0;
            for (int i=0; i<8; ++i)
                investorFile.write(reinterpret_cast<char *> (&investorData),
                                   sizeof(investorData));
        }
        else {
            cerr << "File could not be created." << endl;
            exit(1);
        }
    }
}

investor::~investor()
{
    investorFile.close();
}

void investor::createData(int IDnum)
{
    investorData.ID = IDnum;

    cout << "Enter name for player " << IDnum << ": " << endl;
    if (IDnum == 1)
        cin.ignore();
    cin.getline(investorData.name, 15);
    investorData.cash = 10000.0;

    writeFile();
}

// function to write data taken from the user into the file
void investor::writeFile()
{
    investorFile.seekp((investorData.ID - 1) * sizeof(investorData));
    investorFile.write(reinterpret_cast<char *> (&investorData), sizeof(investorData));
}

void investor::playerStats(int IDnum)
{
    investorFile.seekg((IDnum - 1) * sizeof(investorData));
    investorFile.read(reinterpret_cast<char *> (&investorData), sizeof(investorData));
    if(IDnum == investorData.ID)
    {
    displayData();
    }
}

void investor::displayData()
{



   cout << left << setw(6) << investorData.ID
    << setw(20) << investorData.name <<
    setw(6) << setprecision(5)
    << investorData.cash << endl;
}

void investor::clearStream ()
{
    investorFile.clear();
}

double investor::getCash(int IDnum)
{
    investorFile.seekg((IDnum - 1) * sizeof(investorData));
    investorFile.read(reinterpret_cast<char *> (&investorData), sizeof(investorData));
    if(IDnum == investorData.ID)
    {
    return investorData.cash;
    }
}

void investor::buy(int stockNum, int IDnum, int amt, double sharePrice )
{
    investorFile.seekg((IDnum - 1) * sizeof(investorData));
    investorFile.read(reinterpret_cast<char *> (&investorData), sizeof(investorData));
    if(IDnum == investorData.ID)
    {
        //Commented out is a test to make sure it is modifying the array
      /*  cout << "Starting to purchase for player " << investorData.name << endl;
        cout << "current cash: " << investorData.cash << endl;
        cout << "current investments: " << endl;
        for (int i = 0; i < 4; i++){
        cout << investorData.shares[i] << "  ";
        }
        cout << endl;
    */  investorData.shares[stockNum] = investorData.shares[stockNum] + amt;
        investorData.cash = investorData.cash - (amt * sharePrice);
    /*  cout << "hopefully new stats? " << endl;
        cout << "current cash: " << investorData.cash << endl;
        cout << "current investments: " << endl;
        for (int i = 0; i < 4; i++){
        cout << investorData.shares[i] << "  ";
        }
        cout << endl;
    */
      writeFile();
    }
}

void investor::sell(int stockNum, int IDnum, int amt, double sharePrice )
{
    investorFile.seekg((IDnum - 1) * sizeof(investorData));
    investorFile.read(reinterpret_cast<char *> (&investorData), sizeof(investorData));
    if(IDnum == investorData.ID)
    {
        investorData.shares[stockNum] = investorData.shares[stockNum] - amt;
        investorData.cash = investorData.cash + (amt * sharePrice);
    }
    writeFile();

}

int investor::getShares(int stockNum, int IDnum)
{
    investorFile.seekg((IDnum - 1) * sizeof(investorData));
    investorFile.read(reinterpret_cast<char *> (&investorData), sizeof(investorData));
    if(IDnum == investorData.ID)
    {
        // test to see the returning share values
        //cout << "getting :" << investorData.shares[stockNum] <<  " shares" << endl;
        return investorData.shares[stockNum];
    }

}

void investor::callName(int IDnum)
{
    investorFile.seekg((IDnum - 1) * sizeof(investorData));
    investorFile.read(reinterpret_cast<char *> (&investorData), sizeof(investorData));
    if(IDnum == investorData.ID)
    {
        cout << investorData.name;
    }
}