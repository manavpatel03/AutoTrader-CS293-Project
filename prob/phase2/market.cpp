#include "market.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "ll.h"

using namespace std;

int min(int &a, int &b)
{
    if (a <= b)
        return a;
    else
        return b;
}

market::market(int argc, char **argv)
{
}

void market::start()
{
    string filename = "./output.txt";
    Timevect myorders;
    ifstream file(filename);
    string line;
    // int timeval = 0;
    vector<string> orders;
    while (getline(file, line))
    {
        if (line.find("TL") != string::npos)
        {
            continue;
        }
        if (line.find("!@") != string::npos)
        {
            continue;
        }
        if (line.find("@!") != string::npos)
        {
            break;
        }
        orders.push_back(line);
    }
    for (string order : orders)
    {

        if (order.empty())
        {
            continue;
        }
        hashMap *Map_of_comp = new hashMap();
        istringstream iss(order);
        string initial_time, Broker, buy_or_sell, stock_name, quantity, linear_combination_quantity, price, expiration_time;
        iss >> initial_time >> Broker >> buy_or_sell;
        vector<string> stocks;
        // cout << "Initial Time: " << initial_time << ", Company Name: " << Broker << ", Buy or Sell: " << buy_or_sell;
        int init_time = stoi(initial_time);
        bool buy = (buy_or_sell[0] == 'B');
        while (iss >> stock_name)
        {
            stocks.push_back(stock_name);
        }
        expiration_time = stocks[stocks.size() - 1];
        int expiration_t = stoi(expiration_time);
        linear_combination_quantity = stocks[stocks.size() - 2];
        int li_co_qu = stoi(linear_combination_quantity.substr(1));
        price = stocks[stocks.size() - 3];
        int cost = stoi(price.substr(1));
        stocks.pop_back();
        stocks.pop_back();
        stocks.pop_back();
        if (stocks.size() == 1)
        {
            stocks.push_back("1");
        }
        vector<string> stocks1;
        for (int i = 0; i < stocks.size(); i += 2)
        {
            stocks1.push_back(stocks[i]);
        }
        vector<int> stocks2;
        for (int i = 1; i < stocks.size(); i += 2)
        {
            stocks2.push_back(stoi(stocks[i]));
        }
        // cout << stocks[stocks.size() - 1];
        //  if (stocks.size() % 2 != 0)
        //  {
        //      stocks.push_back("1");
        //  }
        //  for (int i = 0; i < stocks.size(); i += 2)
        //  {
        //      quantity = stocks[i + 1];
        //      stock_name = stocks[i];
        //      cout << ", Stock Name: " << stock_name << ", Quantity: " << quantity << ", Linear Combination Quantity: " << stocks.size() / 2 << ", Price: " << price << ", Expiration Time: " << expiration_time << endl;
        //  }

        // stocks1 -> Comp name stocks2 ->quant cost ->price of LC li_co_qu quantity of deals

        for (int i = 0; i < stocks1.size(); i++)
        {
            Map_of_comp->addorinsert(stocks1[i], stocks2[i]);
        }
        Node2 *S = new Node2();
        char mychar = 'b';
        if (!buy)
            mychar = 's';
        S = S->Newnode2(Map_of_comp, cost, li_co_qu, mychar, init_time, expiration_t);
        vector<Node2 *> Dealholder;
        myorders.Bestdeal(S, Dealholder);
        if (Dealholder.size() == 0)
        {
            myorders.insert(S);
        }
        // else
        // {
        //     for (int i = 0; i < Dealholder.size(); i++)
        //     {
        //         if (S->quant == min(S->quant, Dealholder[i]->quant))
        //         {
        //             Dealholder[i]->quant -= S->quant;
        //             S->quant = 0;
        //             if (S->buy)
        //             {
        //                 cout << S->Broke << " purchased " << li_co_qu << " share of ";
        //                 if (stocks1.size() == 1)
        //                 {
        //                     cout << stocks1[0] << " from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //                 else
        //                 {
        //                     for (int k = 0; k < stocks1.size(); k++)
        //                     {
        //                         cout << stocks1[k] << " " << stocks2[k] << " ";
        //                     }
        //                     cout << "from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //             }
        //             else
        //             {
        //                 cout << Dealholder[i]->Broke << " purchased " << li_co_qu << " share of ";
        //                 if (stocks1.size() == 1)
        //                 {
        //                     cout << stocks1[0] << " from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //                 else
        //                 {
        //                     for (int k = 0; k < stocks1.size(); k++)
        //                     {
        //                         cout << stocks1[k] << " " << stocks2[k] << " ";
        //                     }
        //                     cout << "from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //             }
        //         }
        //         else
        //         {
        //             Dealholder[i]->valid = 0;
        //             S->quant -= Dealholder[i]->quant;
        //             if (S->buy)
        //             {
        //                 cout << S->Broke << " purchased " << Dealholder[i]->quant << " share of ";
        //                 if (stocks1.size() == 1)
        //                 {
        //                     cout << stocks1[0] << " from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //                 else
        //                 {
        //                     for (int k = 0; k < stocks1.size(); k++)
        //                     {
        //                         cout << stocks1[k] << " " << stocks2[k] << " ";
        //                     }
        //                     cout << "from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //             }
        //             else
        //             {
        //                 cout << Dealholder[i]->Broke << " purchased " << Dealholder[i]->quant << " share of ";
        //                 if (stocks1.size() == 1)
        //                 {
        //                     cout << stocks1[0] << " from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //                 else
        //                 {
        //                     for (int k = 0; k < stocks1.size(); k++)
        //                     {
        //                         cout << stocks1[k] << " " << stocks2[k] << " ";
        //                     }
        //                     cout << "from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
        //                 }
        //             }
        //         }
        //     }
        //     if (S->quant > 0)
        //     {
        //         myorders.insert(S);
        //     }
        // }
    }
}