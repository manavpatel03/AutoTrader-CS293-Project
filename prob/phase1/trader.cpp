#include "receiver.h"
#include <vector>
#include <string>
#include "map.h"
class AutoTrader
{
public:
    AutoTrader() {}

    std::string processOrder(const std::string &stock_name, const bool &action, int &price, Map data)
    {
        // Parse the input order
        if (data.check(stock_name))
        {
            vector<int> vals = data.search(stock_name);
            int opp_buffer_index = 1 + int(action);
            int self_buffer_index = 1 + int(!action);
            int estimate = vals[0];
            if (vals[opp_buffer_index] == price)
            {
                // this is to cancel both the buffer out
                if (action)
                {
                    vals[opp_buffer_index] = INT32_MAX;
                }
                else
                    vals[opp_buffer_index] = INT32_MIN;
                data.insert(stock_name, vals);
                return "No Trade";
            }
            // level 1 check, dry run for correctness check
            if (action)
            {
                if (vals[self_buffer_index] > price)
                    return "No Trade";
            }
            else
            {
                if (vals[self_buffer_index] < price)
                    return "No Trade";
            }
            if (action)
            {
                if (estimate < price)
                {
                    vals[self_buffer_index] = INT32_MAX;
                    vals[0] = price;
                    data.insert(stock_name, vals);
                    return stock_name + " " + std::to_string(price) + " s";
                }
                else
                {
                    vals[self_buffer_index] = price;
                    data.insert(stock_name, vals);
                    return "No Trade";
                }
            }
            else
            {
                if (estimate > price)
                {
                    vals[0] = price;
                    vals[self_buffer_index] = INT32_MIN;
                    data.insert(stock_name, vals);
                    return stock_name + " " + std::to_string(price) + " b";
                }
                else
                {
                    vals[self_buffer_index] = price;
                    data.insert(stock_name, vals);
                    return "No Trade";
                }
            }
        }
    }

private:
    std::vector<std::pair<std::string, double>> last_trade_price;

    int find(const std::string &key) const
    {
        int k = -1;
        for (int i = 0; i < last_trade_price.size(); ++i)
        {

            if (last_trade_price[i].first.compare(key) == 0)
            {
                k = i;
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
        AutoTrader at; // Move this line here
        int i = 0;
        Map data;
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
            bool buy = true; // for us i.e if they want to buy then true else false
            if (message[i] == 's')
                buy = false;
            // at this point all the 3 values are with us
            std::string me = at.processOrder(cmpny, buy, price, data);
            std::cout << me << std::endl;
            i += 3;
        }
    }
}
