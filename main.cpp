
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include "investor.h"
#include "company.h"
#include "tech.h"
#include "retail.h"
using namespace std;



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
