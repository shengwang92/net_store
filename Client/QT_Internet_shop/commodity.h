#ifndef COMMODITY_H
#define COMMODITY_H
#include <QMainWindow>
#include <vector>
using namespace std;

class commodity1{

public:
    commodity1();
    commodity1(string);
    int getmoney();
    QString getcommodity();
    int getsize();
    int getcommodity_price();
    int getcount();
    string getSeller_id();
    string getCommodity_id();

private:
    const vector<string> split(const string&,const string&);
    int money=0;
    QString commodity_name;
    string commodity_id,seller_id;
    int commodity_price,count;
};

#endif // COMMODITY_H
