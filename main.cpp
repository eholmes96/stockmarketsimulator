
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "investor.h"
#include "company.h"
#include "tech.h"
#include "retail.h"
using namespace std;

int getrand()
{
    int randnum = rand() % 100 ;
    return randnum;
}

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
    for(int i = 0; i < 4; i++)
    {
    cout << right <<company::getRev(i) << setw(10);
    }
    cout << endl;

    cout << "COSTS: " << setw(6);
    for(int i = 0; i < 4; i++)
    {
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





int main()
{
    //Initialize Amt of players and Quarters
    int numplayersin;
    int numyears;
    cout << "Welcome to the Investment Simulator" << endl
         << "How many player will be participating? (8 max) " << endl;
    cin >> numplayersin;
    cout << "How many game years would you like to play?" << endl;
    cin >> numyears;

    static int numPlayersFin = numplayersin;
    static int numQuartersFin = 4 * numyears;

    //Show rules
    cout << "Before we get started, let's go over how this games works" << endl
         << "Each investor starts with $10,000 cash to invest with" << endl
         << "Each quarter, every player has a chance to change their \n"
         << "investments, but be careful as each player can only has \n"
         << "one chance per quarter to modify their profile " << endl;
    cout << endl;
    cout << "The following is the list of commands during the simulation: " << endl
         << "    ticker:    Shows all stock prices" << endl
         << "    qreports:  Shows statistics on company"  << endl
         << "    invest:    Brings up menu to check portfolio and change investments" << endl
         << "    continue:  End current quarter and advance to next quarter" << endl
         << "    help:      show this list again " << endl;

    //Initialize all investors
    investor players("playerinfo.bin");

        for (int c1 = 1; c1 <= numPlayersFin; c1++)
    {
        players.createData(c1);

    }
        players.clearStream();

    //Show player stats
    cout << left << setw(6) << "ID"
    << setw(20) << "Name" <<
    setw(6) << "Cash" << endl;

        for(int c1 = 1; c1 <= numPlayersFin; c1++)
        {
            players.playerStats(c1);
        }


    //Initialize all companies
      tech NOLG;
      retail CLTH;

    //start functions
      NOLG.startRevenue(3);
      CLTH.startRevenue(6);

      NOLG.startCosts(3);
      CLTH.startCosts(6);

      NOLG.startProfit();
      CLTH.startProfit();

      NOLG.startUsers(4);
      NOLG.startStock(3.5);
      CLTH.startSales();
      CLTH.startStock(5.1);


     //advance 1 quar
      NOLG.setRevenues(3);
      CLTH.setRevenues(6);

      NOLG.setCosts(3);
      CLTH.setCosts(6);


      NOLG.setProfit();
      CLTH.setProfit();

      NOLG.setUsers();
      NOLG.setStock();
      CLTH.setSales();
      CLTH.setStock();

//Start main section

//set up timing: by quarters
int quar;
int *quarPtr;
quarPtr = &quar;
*quarPtr = 0;
//play until all quarters done;
while(*quarPtr < numQuartersFin)
{

            //iterate all companies
      NOLG.setRevenues(3);
      CLTH.setRevenues(6);

      NOLG.setCosts(3);
      CLTH.setCosts(6);


      NOLG.setProfit();
      CLTH.setProfit();

      NOLG.setUsers();
      NOLG.setStock();
      CLTH.setSales();
      CLTH.setStock();

    cout << "This is quarter " << *quarPtr << endl;

    bool done = 0;
    while(!done)
    {
        cout << "what would you like to do?" << endl;
        string cmd;
        getline(cin, cmd);


        if(cmd == "continue")
        {
           cout << "ending all turns for this quarter" << endl;
           done = 1;
        }
        else if (cmd == "ticker")
        {
            cout << "--------Stock Ticker--------" << endl;
            cout << "Name" << right << setw(10) << "Q1"  << setw(10) << "Q2"  << setw(10) << "Q3"  << setw(10) << "Q4" << endl;
            cout << left << "NOLG -     " << setw(10);
                for(int i = 0; i < 4; i++)
                {
                    cout << NOLG.getStock(i) << setw(10);
                }
            cout << endl;
            cout << left << "CLTH -     " << setw(10);
                for(int i = 0; i < 4; i++)
                {
                    cout << CLTH.getStock(i) << setw(10);
                }
            cout << endl;

        }
        else if (cmd == "help")
        {
             cout << "The following is the list of commands during the simulation: " << endl
            << "    ticker:    Shows all stock prices" << endl
            << "    invest:    Brings up menu to check portfolio and change investments" << endl
            << "    qreports:  Shows statistics on company"  << endl
            << "    continue:  End current quarter and advance to next quarter" << endl
            << "    help:      show this list again " << endl;

        }
        else if (cmd == "invest" )
        {
            cout << "For Reference: " << endl;
                //Show all players and IDs
                cout << left << setw(6) << "ID"
                << setw(20) << "Name" <<
                setw(6) << "Cash" << endl;

            for(int c1 = 1; c1 <= numPlayersFin; c1++)
            {
                players.playerStats(c1);
            }
            int ID;
            cout << "Player ID?" << endl;

            cin >> ID;


            if(ID <= numPlayersFin){
                bool inDone = 0;
                while(!inDone){
                    cout << "your current investments are: " << endl;
                    cout  <<"Company " << setw(10) << " shares " << setw(10) << " Market Value " << setw(10) << endl;
                    cout << "NOLG: " << setw(10) << players.getShares(0, ID) <<  setw(10)
                        << NOLG.getStock(3)*players.getShares(0, ID) << endl;
                    cout << "CLTH:     " << setw(10) << players.getShares(1,ID) << setw(10)
                        << CLTH.getStock(3)*players.getShares(1, ID) << endl;

                    cout << endl;
                    cout << "Cash:                  $" << players.getCash(ID) << endl;
                    double mVal = CLTH.getStock(3)*players.getShares(1, ID) + NOLG.getStock(3)*players.getShares(0, ID);
                    cout << "Total value of stocks: $" << mVal << endl;
                    cout << endl;


                    cout << "Type 'buy' or 'sell' to modify your investments" << endl;
                    cout << "or type 'continue' if you are done investing";
                    string icmd;
                    getline(cin, icmd);


                        if (icmd == "buy")
                        {
                            cout << "which company?" << endl;
                            string csel;
                            getline(cin,csel);
                            if(csel == "NOLG")
                            {
                                cout << "how many shares?" << endl;
                                int numShares;
                                cin >> numShares;
                                double cash = players.getCash(ID);
                                cout << "cash: " << cash << "   price: " <<  NOLG.getStock(3) << endl;
                                if (NOLG.getStock(3) * numShares <= cash)
                                {
                                    players.buy(0, ID, numShares, NOLG.getStock(3));
                                    players.clearStream();
                                    cout << "Trying to purchase " << numShares << " of NOLG" << endl;
                                    cout << "New shares? " << players.getShares(0, ID) << endl;
                                    if (players.getShares(0,ID) == numShares)
                                        cout << "Success! " << endl;
                                    else
                                        cout << "oops" << endl;
                                } else
                                {
                                    cout << "Not enough funds! Try again" << endl;
                                }

                            } else if (csel == "CLTH")  //here
                            {
                                    cout << "how many shares?" << endl;
                                    int numShares;
                                    cin >> numShares;
                                    double cash = players.getCash(ID);
                                    cout << "cash: " << cash << "   price: " <<  CLTH.getStock(3) << endl;
                                    if (CLTH.getStock(3) * numShares <= cash)       //here
                                    {
                                        players.buy(1, ID, numShares, CLTH.getStock(3)); //here x2
                                        players.clearStream();
                                        cout << "Trying to purchase " << numShares << " of CLTH" << endl;
                                        cout << "New shares? " << players.getShares(1, ID) << endl; //here
                                        if (players.getShares(1,ID) == numShares)   //here
                                            cout << "Success! " << endl;
                                        else
                                            cout << "oops" << endl;
                                    } else
                                    {
                                        cout << "Not enough funds! Try again" << endl;
                                    }
                                }//end CLTH
                                else
                                {
                                    cout << "That's no company, try again" << endl;
                                }

                        }
                        else if (icmd == "sell")
                        {
                            cout << "which company?" << endl;
                            string csel;
                            getline(cin,csel);
                            if(csel == "NOLG")
                            {
                                cout << "how many shares?" << endl;
                                int numShares;
                                cin >> numShares;
                                int shOwned = players.getShares(0,ID);

                                if (numShares <= shOwned)
                                {
                                    players.sell(0, ID, numShares, NOLG.getStock(3));
                                    players.clearStream();
                                    cout << "Trying to sell " << numShares << " of NOLG" << endl;
                                    cout << "New shares? " << players.getShares(0, ID) << endl;
                                    if (shOwned > numShares)
                                        cout << "Success! " << endl;
                                    else
                                        cout << "oops" << endl;
                                } else
                                {
                                    cout << "Not enough funds! Try again" << endl;
                                }
                            }// end NOLG
                            else if (csel == "CLTH")
                            {
                                cout << "how many shares?" << endl;
                                int numShares;
                                cin >> numShares;
                                int shOwned = players.getShares(1,ID); //here

                                if (numShares <= shOwned)
                                {
                                    players.sell(1, ID, numShares, CLTH.getStock(3)); //here x2
                                    players.clearStream();
                                    cout << "Trying to sell " << numShares << " of CLTH" << endl; //here
                                    cout << "New shares? " << players.getShares(1, ID) << endl; //here
                                    if (shOwned > numShares)
                                        cout << "Success! " << endl;
                                    else
                                        cout << "oops" << endl;
                                } else
                                {
                                    cout << "Not enough funds! Try again" << endl;
                                }

                            }//end CLTH
                        }//end sell
                        else if(icmd == "continue")
                        {
                            inDone = 1;
                        }

                        else{
                            cout << "Sorry, try again" << endl;
                        }



            } // end while


        } //end If ID
        else
            {
                cout << "that's not a player!" << endl;
            }
        }//end invest
        else if (cmd == "qreports")
        {
            string comp;
            cout << "What company? " << endl;
            getline(cin, comp);
            if(comp == "NOLG")
            {
                NOLG.print();
            }
            else if(comp == "CLTH")
            {
                CLTH.print();
            }
        }
        else
        {
            cout << "sorry, wrong command! \n" << "try typing 'help' " << endl;
        }



    }

        *quarPtr += 1;

}
    cout << "End of game: the results are: " << endl;
    double total[numPlayersFin];
    int winner;
    for(int j = 1; j <= numPlayersFin; j++)
    {
        total[j] = players.getCash(j) + players.getShares(0, j) * NOLG.getStock(3) +
                                players.getShares(1, j) * CLTH.getStock(3);
        cout << "Total for ";
        players.callName(j);
        cout << " is $" << total[j] << endl;
        if(total[j] > winner)
        {
            winner = j;
        }
    }

    cout << endl;
    cout << "The winner is ";
    players.callName(winner);
    cout << endl;



cout << "THE END" << endl;




}//endmain
