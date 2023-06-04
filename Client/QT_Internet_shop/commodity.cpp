#include "commodity.h"
#include "ui_mainwindow.h"
#include<vector>

commodity1::commodity1(){
}
commodity1::commodity1(string data){

    vector<string> good = split(data,",");

    QString s=QString::fromStdString(good[1]);
    commodity_name=s;
    commodity_id=good[0];
    seller_id=good[2];
    commodity_price=stoi(good[3]);
    count=stoi(good[4]);

}

int commodity1::getmoney(){
    return money;
}
int commodity1::getsize(){
    return commodity_name.size();
}

int commodity1::getcommodity_price(){
    return commodity_price;
}
QString commodity1::getcommodity(){
    return commodity_name;
}
int commodity1::getcount(){
    return count;
}
string commodity1::getSeller_id(){
    return seller_id;
}
string commodity1::getCommodity_id(){
    return commodity_id;
}
const vector<string> commodity1::split(const string& str, const string& pattern) {
    vector<string> result;
    string::size_type begin, end;

    end = str.find(pattern);
    begin = 0;

    while (end != string::npos) {
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end - begin));
        }
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }

    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }
    return result;
}
