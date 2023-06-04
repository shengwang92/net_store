#ifndef MEMBER_H
#define MEMBER_H
#include <QApplication>
#include <string>
#include <iostream>
#include"HTTPRequest.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

class member
{
public:
    member(string = "s", string = "s");
    string getUid() const;
    string getName() const;
    string getEmail() const;
    int getMoney() const;
    void setUid(string);
    void setName(string);
    void setEmail(string);
    void setMoney(int);
    int store_balance(string , int );
    string upload_commodity(string , string , int , int);
    string view_commodity() ;
    string buy_commodity(string , string , string , int );

private:
    static string uid, name, email,commodity_id;
    static int money;

};

#endif // MEMBER_H
