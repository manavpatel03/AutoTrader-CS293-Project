#include "receiver.h"
#include <vector>
#include <string>
#include "map.h"
class AutoTrader
{
public:
    AutoTrader() {}

    std::string processOrder(const std::string &stock_name, const bool &action, int &price)
    {
        // Parse the input order
        
        int index = find(stock_name);
      
        if (index == -1 && action == false)
        {
            // First trade, always execute the order
            last_trade_price.push_back({stock_name, price});
            return stock_name + " " + std::to_string(price) + " " + "s";
        }
        else if (index == -1 && action == true)
        {
            // First trade, always execute the order
            last_trade_price.push_back({stock_name, price});
            return stock_name + " " + std::to_string(price) + " " + "b";
        }
        else
        {
            if (action == false && price > last_trade_price[index].second)
            {
                // Buy when the price is lower than the last traded price
                last_trade_price[index].second = price;
                return stock_name + " " + std::to_string(price) + " s";
            }
            else if (action == true && price < last_trade_price[index].second)
            {
                // Sell when the price is higher than the last traded price
                last_trade_price[index].second = price;
                return stock_name + " " + std::to_string(price) + " b";
            }
        }

        // If no trade is executed, return "No Trade"
        return "No Trade";
    }

private:
    std::vector<std::pair<std::string, double>> last_trade_price;

    int find(const std::string &key) const
    {
        int k=-1;
        for (int i = 0; i < last_trade_price.size(); ++i)
        {
            
            if (last_trade_price[i].first.compare(key) == 0)
            {
                k=i;
                break;
            }
        }
        return k;
    }

    // std::vector<std::string> split(const std::string &input, char delimiter)
    // {
    //     std::vector<std::string> tokens;
    //     std::string token;
    //     size_t start = 0;
    //     size_t end = input.find(delimiter);

    //     while (end != std::string::npos)
    //     {
    //         token = input.substr(start, end - start);
    //         tokens.push_back(token);
    //         start = end + 1;
    //         end = input.find(delimiter, start);
    //     }

    //     tokens.push_back(input.substr(start, end));
    //     return tokens;
    // }
};

int main(int argc, char **argv)
{
    Receiver rcv;
    sleep(5);
    std::string message = rcv.readIML();
    if (argc < 2 ||
        (argv[1][0] != '1' && argv[1][0] != '2' && argv[1][0] != '3'))
    {
        std::cout << "Give mode of operation:\n 0 for part 1 \n"
                     " 1 for testing part2 \n"
                     " 2 for testing part3 \n"
                  << std::endl;
    }
    char which = argv[1][0];
    if (which == '1')
    {
        AutoTrader at;  // Move this line here
        int i = 0;
        while (i < message.length())
        {
            std::string cmpny = "";
            while (message[i] != 32)
            {
                cmpny.push_back(message[i]);
                i++;
            }
            i++;
            std::string price_holder = "";
            while (message[i] != 32)
            {
                price_holder.push_back(message[i]);
                i++;
            }
            i++;
            int price = stoi(price_holder);
            bool buy = true; // for us i.e if we want to buy then true else false
            if (message[i] == 'b')
                buy = false;
            std::string me=at.processOrder(cmpny,buy,price);
            std::cout << me << std::endl;
            i += 3;
        }
          
    }
}

