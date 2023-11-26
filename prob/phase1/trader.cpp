#include "receiver.h"
#include <vector>
#include <string>
#include "map.h"
// #include "map2.h"
#include "ll.h"
class AutoTrader
{
public:
    AutoTrader() {}

    std::string processOrder(const std::string &stock_name, const bool &action, int &price, Map data)
    {
        // Parse the input order
        vector<int> vals(3);
        if (data.check(stock_name))
        {
            vals = data.search(stock_name);
        }
        else
        {
            if (action)
            {
                vals[0] = INT32_MIN;
            }
            else
            {
                vals[0] = INT32_MAX;
            }                    // estimate
            vals[1] = INT32_MIN; // buy buffer i.e. the customer wants to buy
            vals[2] = INT32_MAX; // sell buffer i.e. the customer wants to sell
        }
        int opp_buffer_index = 1 + int(action);
        int self_buffer_index = 1 + int(!action);
        int estimate = vals[0];
        // level 1 check, dry run for correctness check
        if (action)
        {
            if (vals[self_buffer_index] >= price)
                return "No Trade";
        }
        else
        {
            if (vals[self_buffer_index] <= price)
                return "No Trade";
        }
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
        if (action)
        {
            if (estimate < price)
            {
                vals[self_buffer_index] = INT32_MIN;
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
                vals[self_buffer_index] = INT32_MAX;
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
    bool dlr = false;
    // if (argc < 2 ||
    // std::cout << message << std::endl;
    if (argv[1][0] != '1' && argv[1][0] != '2' && argv[1][0] != '3')
    {
        std::cout << "Give mode of operation:\n 0 for part 1 \n"
                     " 1 for testing part2 \n"
                     " 2 for testing part3 \n"
                  << std::endl;
    }
    char which = argv[1][0];
    if (which == '1')
    {
        AutoTrader at;
        Map data;
        bool buffer_size_check = true;
        while (buffer_size_check)
        {
            std::string message = rcv.readIML();
            if (message.find("$") != std::string::npos)
            {
                buffer_size_check = false;
                rcv.terminate();
            }
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
    if (which == '2')
    {
        int ja = 0;
        LinkedList Combinations;
        Com_list *comlist = new Com_list();
        vector<int> first_elem;
        int i = 0;
        int j = 0;
        bool buffer_size_check = true;
        int final_profit = 0;
        while (buffer_size_check)
        {
            std::string message = rcv.readIML();
            if (message.find("$") != std::string::npos)
            {
                buffer_size_check = false;
                rcv.terminate();
            }
            while (i < message.length())
            {

                char last_char;
                bool price_equal = 0;
                hashMap Storage;
                int price = 0;
                first_elem.push_back(i);
                while (message[i] != '#')
                {
                    std::string cmpny = "";
                    while (message[i] != 32)
                    {
                        if (message[i] >= 48 && message[i] <= 57)
                            price_equal = true;
                        cmpny.push_back(message[i]);
                        i++;
                    }
                    // std::cout << cmpny << endl;
                    i++;
                    std::string quantity = "";
                    if (price_equal)
                    {
                        last_char = message[i];
                        // cout << "fdf : " << last_char << endl;
                        price_equal = false;
                        // cout << "this is the value(a) : " << ++ja << cmpny << endl;
                        price = stoi(cmpny);
                        comlist->addtolist(price, last_char, j);
                        i += 3;
                        j++;
                        break;
                    }
                    while (message[i] != 32)
                    {
                        quantity.push_back(message[i]);
                        i++;
                    }

                    // cout << "this is the value : " << ++ja << quantity << endl;
                    comlist->addtolist(cmpny, stoi(quantity), j);
                    Storage.addorinsert(cmpny, stoi(quantity));
                    i++;
                    //
                }
                if (last_char == 's')
                {
                    price *= -1;
                }
                if (last_char == 'b')
                {
                    Storage.makenegev();
                }
                int plchlder;
                vector<int> validyans;
                if (comlist->checkcancel(comlist->LCs[j - 1], validyans))
                {
                    // cout << "Removed : ";
                    // for (int nope = 0; nope < validyans.size(); nope++)
                    //     cout << validyans[nope] << " " << endl;
                    Combinations.remove_invalid(validyans);
                    validyans.clear();
                }
                else
                {
                    Combinations.addtoLC(Storage, price, j - 1);
                    validyans = Combinations.getarbitrage(plchlder);
                    // cout << "hi" << endl;
                    // cout << "fsfsdfdfsdfsd" << endl;
                    // cout << "rizzzzz" << endl;
                    // Combinations.Display();
                    // vector<int> *S = ;
                    // cout << "rizzzzz" << endl;
                    // cout << validyans.size();
                }
                if (validyans.size() == 0)
                {
                    cout << "No Trade" << std::endl;
                }
                else
                {
                    final_profit += plchlder;
                    for (int u = validyans.size() - 1; u >= 0; u--)
                    {
                        int k = validyans[u];
                        k = first_elem[k];
                        while (message[k] != '#')
                        {
                            cout << message[k];
                            if (message[k + 2] == '#')
                            {
                                if (message[k + 1] == 'b')
                                    cout << "s#";
                                else if (message[k + 1] == 's')
                                    cout << "b#";
                                break;
                            }
                            k++;
                        }
                        cout << endl;
                    }
                }
                vector<int> delrange(validyans);
                // cout << "My valid vect : ";
                // for (int fgh = 0; fgh < validyans.size(); fgh++)
                //     cout << validyans[fgh] << " ";
                // cout << endl;
                // Combinations.Display();
                Combinations.remove_invalid(delrange);
                // cout << "done" << endl;
                // now write LC logic
            }
        }
        cout << final_profit;
    }

    if (which == '3')
    {
        int ja = 0;
        LinkedList Combinations;
        Com_list *comlist = new Com_list();
        vector<int> first_elem;
        int i = 0;
        int j = 0;
        bool buffer_size_check = true;
        int final_profit = 0;
        while (buffer_size_check)
        {
            std::string message = rcv.readIML();
            if (message.find("$") != std::string::npos)
            {
                buffer_size_check = false;
                rcv.terminate();
            }
            while (i < message.length())
            {

                char last_char;
                bool price_equal = 0;
                hashMap Storage;
                int price = 0;
                first_elem.push_back(i);
                while (message[i] != '#')
                {
                    int overall_quant = 0;
                    std::string cmpny = "";
                    while (message[i] != 32)
                    {
                        if (message[i] >= 48 && message[i] <= 57)
                            price_equal = true;
                        cmpny.push_back(message[i]);
                        i++;
                    }
                    // std::cout << cmpny << endl;
                    i++;
                    std::string quantity = "";
                    if (price_equal)
                    {
                        string quant_place;
                        while (message[i] != 32)
                        {
                            quant_place.push_back(message[i++]);
                        }
                        overall_quant = stoi(quant_place);
                        last_char = message[i];
                        // cout << "fdf : " << last_char << endl;
                        price_equal = false;
                        // cout << "this is the value(a) : " << ++ja << cmpny << endl;
                        price = stoi(cmpny);
                        comlist->addtolist(price, last_char, j);
                        i += 3;
                        j++;
                        break;
                    }
                    while (message[i] != 32)
                    {
                        quantity.push_back(message[i]);
                        i++;
                    }

                    // cout << "this is the value : " << ++ja << quantity << endl;
                    comlist->addtolist(cmpny, stoi(quantity), j);
                    Storage.addorinsert(cmpny, stoi(quantity));
                    i++;
                    //
                }
                if (last_char == 's')
                {
                    price *= -1;
                }
                if (last_char == 'b')
                {
                    Storage.makenegev();
                }
                int plchlder;
                vector<int> validyans;
                if (comlist->checkcancel(comlist->LCs[j - 1], validyans))
                {
                    Combinations.remove_invalid(validyans);
                    validyans.clear();
                }
                else
                {
                    Combinations.addtoLC(Storage, price, j - 1);
                    validyans = Combinations.getarbitrage(plchlder);
                    // cout << "hi" << endl;
                    // cout << "fsfsdfdfsdfsd" << endl;
                    // cout << "rizzzzz" << endl;
                    // Combinations.Display();
                    // vector<int> *S = ;
                    // cout << "rizzzzz" << endl;
                    // cout << validyans.size();
                }
                if (validyans.size() == 0)
                {
                    cout << "No Trade" << std::endl;
                }
                else
                {
                    final_profit += plchlder;
                    for (int u = validyans.size() - 1; u >= 0; u--)
                    {
                        int k = validyans[u];
                        k = first_elem[k];
                        while (message[k] != '#')
                        {
                            cout << message[k];
                            if (message[k + 2] == '#')
                            {
                                if (message[k + 1] == 'b')
                                    cout << "s#";
                                else if (message[k + 1] == 's')
                                    cout << "b#";
                                break;
                            }
                            k++;
                        }
                        cout << endl;
                    }
                }
                vector<int> delrange(validyans);
                // cout << "My valid vect : ";
                // for (int fgh = 0; fgh < validyans.size(); fgh++)
                //     cout << validyans[fgh] << " ";
                // cout << endl;
                // Combinations.Display();
                Combinations.remove_invalid(delrange);
                // cout << "done" << endl;
                // now write LC logic
            }
        }
        cout << final_profit;
    }

    // AutoTrader at; // Move this line here
}
