#include"member.h"
#include<string>
using namespace std;

string member::uid="";
string member::name="";
string member::email="";
int member::money=0;

member::member(string name, string email) {
    this->name = name;
    this->email = email;
}

string member::getUid() const {
    return uid;
}

string member::getName() const {
    return name;
}

string member::getEmail() const {
    return email;
}

int member::getMoney() const {
    return money;
}

void member::setUid(string uid) {
    this->uid = uid;
}

void member::setName(string name) {
    this->name = name;
}

void member::setEmail(string email) {
    this->email = email;
}

void member::setMoney(int money) {
    this->money = money;
}

//儲值到現有帳號
int member::store_balance(string _id, int balance_member){
    string balance = to_string(balance_member);
       try
       {
           http::Request request{ "http://140.113.213.57:5125/store_balance" };
           const string body = "{\"_id\": \"" + _id + "\", \"balance_member\": \"" + balance + "\"}";
           const auto response = request.send("POST", body, {
               {"Content-Type", "application/json"}
               });
           return stoi(string{ response.body.begin(), response.body.end() });
       }
       catch (const exception& e)
       {
            cerr << e.what() ;
       }
       return -1;
}

//上傳商品售賣
string member::upload_commodity(string _id_seller, string name_commodity, int price, int inventory) {
    string pricestr = to_string(price);
    string inventorystr = to_string(inventory);
    try
    {
        http::Request request{ "http://140.113.213.57:5125/upload_commodity" };
        const string body = "{\"_id_seller\": \"" + _id_seller + "\", \"name_commodity\": \"" + name_commodity + "\", \"price\": \"" + pricestr + "\", \"inventory\": \"" + inventorystr + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}

//查看商品列表
string member::view_commodity() {
    try
    {
        // you can pass http::InternetProtocol::V6 to Request to make an IPv6 request
        http::Request request{ "http://140.113.213.57:5125/view_commodity" };

        // send a get request
        const auto response = request.send("GET");
        //cout << string{ response.body.begin(), response.body.end() } << '\n'; // print the result
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }
    return "ERROR";
}

//B向A購買商品
string member::buy_commodity(string _id_buyer, string _id_seller, string _id_commdity, int number) {
    string numberstr = to_string(number);
    try
    {
        http::Request request{ "http://140.113.213.57:5125/buy_commodity" };
        const string body = "{\"_id_buyer\": \"" + _id_buyer + "\", \"_id_seller\": \"" + _id_seller + "\", \"_id_commdity\": \"" + _id_commdity + "\", \"number\": \"" + numberstr + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}
