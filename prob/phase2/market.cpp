#include "market.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "ll.h"

using namespace std;

bool srch(vector<string> &a, string b)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == b)
            return true;
    }
    return false;
}
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
    hashMap *qunttrade_b = new hashMap();
    hashMap *qunttrade_s = new hashMap();
    hashMap *net = new hashMap();
    int completed_trades = 0;
    int shares_traded = 0;
    int moni = 0;
    vector<string> broker_s;
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
        if (!srch(broker_s, Broker))
            broker_s.push_back(Broker);
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
        S = S->Newnode2(Map_of_comp, cost, li_co_qu, mychar, init_time, expiration_t, Broker);
        vector<Node2 *> Dealholder;
        myorders.Bestdeal(S, Dealholder);
        if (Dealholder.size() == 0)
        {
            // cout << "I am here" << endl;
            myorders.insert(S);
        }
        else
        {
            for (int i = 0; i < Dealholder.size(); i++)
            {
                if (S->quant == min(S->quant, Dealholder[i]->quant))
                {
                    completed_trades++;
                    // if(Dealholder[i]->Broke != S->Broke) continue;
                    Dealholder[i]->quant -= S->quant;
                    shares_traded += S->quant;
                    moni += S->quant * Dealholder[i]->price;
                    if (S->buy)
                    {
                        qunttrade_b->addorinsert(S->Broke, S->quant);
                        qunttrade_s->addorinsert(Dealholder[i]->Broke, S->quant);
                        net->addorinsert(S->Broke, (-1) * S->quant * Dealholder[i]->price);
                        net->addorinsert(Dealholder[i]->Broke, S->quant * Dealholder[i]->price);
                        S->quant = 0;

                        cout << S->Broke << " purchased " << li_co_qu << " share of ";
                        if (stocks1.size() == 1)
                        {
                            cout << stocks1[0] << " from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                        else
                        {
                            for (int k = 0; k < stocks1.size(); k++)
                            {
                                cout << stocks1[k] << " " << stocks2[k] << " ";
                            }
                            cout << "from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                    }
                    else
                    {
                        qunttrade_s->addorinsert(S->Broke, S->quant);
                        qunttrade_b->addorinsert(Dealholder[i]->Broke, S->quant);
                        net->addorinsert(S->Broke, S->quant * Dealholder[i]->price);
                        net->addorinsert(Dealholder[i]->Broke, -1 * S->quant * Dealholder[i]->price);
                        S->quant = 0;

                        cout << Dealholder[i]->Broke << " purchased " << li_co_qu << " share of ";
                        if (stocks1.size() == 1)
                        {
                            cout << stocks1[0] << " from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                        else
                        {
                            for (int k = 0; k < stocks1.size(); k++)
                            {
                                cout << stocks1[k] << " " << stocks2[k] << " ";
                            }
                            cout << "from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                    }
                }
                else
                {
                    shares_traded += Dealholder[i]->quant;

                    moni += Dealholder[i]->quant * Dealholder[i]->price;
                    completed_trades++;
                    Dealholder[i]
                        ->valid = 0;
                    S->quant -= Dealholder[i]->quant;
                    if (S->buy)
                    {
                        qunttrade_b->addorinsert(S->Broke, Dealholder[i]->quant);
                        qunttrade_s->addorinsert(Dealholder[i]->Broke, Dealholder[i]->quant);

                        net->addorinsert(S->Broke, (-1) * Dealholder[i]->quant * Dealholder[i]->price);
                        net->addorinsert(Dealholder[i]->Broke, Dealholder[i]->quant * Dealholder[i]->price);
                        cout << S->Broke << " purchased " << Dealholder[i]->quant << " share of ";
                        if (stocks1.size() == 1)
                        {
                            cout << stocks1[0] << " from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                        else
                        {
                            for (int k = 0; k < stocks1.size(); k++)
                            {
                                cout << stocks1[k] << " " << stocks2[k] << " ";
                            }
                            cout << "from " << Dealholder[i]->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                    }
                    else
                    {
                        qunttrade_s->addorinsert(S->Broke, Dealholder[i]->quant);
                        qunttrade_b->addorinsert(Dealholder[i]->Broke, Dealholder[i]->quant);
                        net->addorinsert(S->Broke, Dealholder[i]->quant * Dealholder[i]->price);
                        net->addorinsert(Dealholder[i]->Broke, -1 * Dealholder[i]->quant * Dealholder[i]->price);
                        cout << Dealholder[i]->Broke << " purchased " << Dealholder[i]->quant << " share of ";
                        if (stocks1.size() == 1)
                        {
                            cout << stocks1[0] << " from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                        else
                        {
                            for (int k = 0; k < stocks1.size(); k++)
                            {
                                cout << stocks1[k] << " " << stocks2[k] << " ";
                            }
                            cout << "from " << S->Broke << " for $" << Dealholder[i]->price << "/share" << endl;
                        }
                    }
                }
            }
            if (S->quant > 0)
            {
                myorders.insert(S);
            }
        }
    }
    cout << "---End of Day---" << endl;
    cout << "Total Amount of Money Transferred: $" << moni << endl;
    cout << "Number of Completed Trades: " << completed_trades << endl;
    cout << "Number of Shares Traded: " << shares_traded << endl;
    for (int i = 0; i < broker_s.size(); i++)
    {
        cout << broker_s[i] << " bought " << qunttrade_b->search_Val(broker_s[i]) << "and sold " << qunttrade_s->search_Val(broker_s[i]) << "for a net transfer of $" << net->search_Val(broker_s[i]) << endl;
    }
}