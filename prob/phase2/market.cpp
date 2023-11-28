#include "market.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "ll.h"

using namespace std;

market::market(int argc, char **argv)
{
}

void market::start()
{
    string filename = "./output.txt";
    ifstream file(filename);
    string line;
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
        linear_combination_quantity = stocks[stocks.size() - 2];
        price = stocks[stocks.size() - 3];
        stocks.pop_back();
        stocks.pop_back();
        stocks.pop_back();
        if (stocks.size() == 1)
        {
            stocks.push_back("1");
        }
        cout << stocks[stocks.size() - 1];
        if (stocks.size() % 2 != 0)
        {
            stocks.push_back("1");
        }
        for (int i = 0; i < stocks.size(); i += 2)
        {
            quantity = stocks[i + 1];
            stock_name = stocks[i];
            cout << ", Stock Name: " << stock_name << ", Quantity: " << quantity << ", Linear Combination Quantity: " << stocks.size() / 2 << ", Price: " << price << ", Expiration Time: " << expiration_time << endl;
        }
    }
}