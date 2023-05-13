#ifndef Commodity_H
#define Commodity_H

#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Commodity {
private:
    string commodity_id, seller_id, name_commodity;
    int price, inventory;

    const vector<string> split(const string& str, const string& pattern);
    const vector<string> secondSpilitCommosity(string& str);
    string formatString(string param, int length);
public:
    Commodity();
    Commodity(string process_data_string);
    void viewCommodity(int index);
    string getCommodityId() const;
    string getSellerId() const;
    int getPrice() const;
    int getInventory() const;

};

#endif // !Commodity_H