#include <iostream>
#include <fstream>
#include <string>
#include"HTTPRequest.hpp"
#include"Member.h"
#include"Commodity.h"
#include"Commodity_List.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

void preprocessing(string&);   //�e�m�B�z
void help();                                                   //�C���L�C��
void clear();                                                  //�M��
string enroll_member(string, string, string);                  //���U�s���|��
string login_member(string, string);                           //�n�J�w�����|���b��
int store_balance(string, int);                                //�x�Ȩ�{���b��
string upload_commodity(string, string, int, int);             //�W�ǰӫ~���
string view_commodity();                                       //�d�ݰӫ~�C��
string buy_commodity(string, string, string, int);             //B�VA�ʶR�ӫ~

//�ھڿ�J����ʧ@
int main()
{
    bool judge = TRUE;
    string userinput = "";
    string view = "";
    string feasible = "";                    //Succes or Fail
    string user_id = "", seller_id = "", commodity_id = "";     //user_id seller_id commodity_id
    CommodityList goods = CommodityList(view_commodity());
    Member user;

    cout << "You can input help to see all instruction" << endl;
    cout << "Input leave to exit program" << endl;

    while (judge == TRUE) {
        cout << "What mode do you want to enter" << endl;
        cin >> userinput;

        if (userinput == "enroll") {                //�бb��
            string user_name, user_email, passwd;
            cout << "Input your user name: ";
            cin >> user_name;
            cout << "Input your email account: ";
            cin >> user_email;
            cout << "Input your password: ";
            cin >> passwd;
            user = Member(user_name, user_email);
            user.setUid(enroll_member(user_name, user_email, passwd)); //�Ыرb���ño��user_id
            user.setMoney(store_balance(user.getUid(), 0));
        }

        else if (userinput == "logout") {          //�n�J
            string intput_email, input_passwd;
            cout << "Input your email account: ";
            cin >> intput_email;
            cout << "Input your password: ";
            cin >> input_passwd;
            user.setEmail(intput_email);
            user.setUid(login_member(intput_email, input_passwd)); //�n�J�ño��Member
            user.setMoney(store_balance(user.getUid(), 0));
        }

        else if (userinput == "money") {           //�x��
            int money;
            cout << "How much money you want to store: ";
            cin >> money;
            user.setMoney(store_balance(user.getUid(), money)); //�o���x�ȫ᪺���B
            cout << "The money you have now is " << user.getMoney() << endl;
        }

        else if (userinput == "sell") {            //��amode
            string commodity_name;
            int price, inventory;
            cout << "What is the name of this commodity: ";
            cin >> commodity_name;
            cout << "How much price do you want to set: ";
            cin >> price;
            cout << "How much commodity do you want to store: ";
            cin >> inventory;
            commodity_id = upload_commodity(user_id, commodity_name, price, inventory);
        }

        else if (userinput == "view") {            //�ݰӫ~
            view = view_commodity();
            goods = CommodityList(view);
            goods.viewCommodites();
        }

        else if (userinput == "buy") {             //�R�amode
            int  which_commodity=2;
            int  inventory;
            cout << "Enter number less than 0 to exits" << endl;

            while (which_commodity > 0) {
                cout << "What commodity do you want to buy (Please enter the commodity number): ";
                cin >> which_commodity;
                cout << "How many commodity do you want to buy: ";
                cin >> inventory;
                if (user.getMoney() < goods.viewPrice(which_commodity)) {
                    cout << "Insufficient balance (You need to top up your online account)";
                }
                else if (inventory < goods.viewInventory(which_commodity)) {
                    cout << "Inventory shortage";
                }
                else {
                    feasible = buy_commodity(user.getUid(), goods.viewSellerId(which_commodity), goods.viewCommodityId(which_commodity), inventory);
                }
            }
        }

        else if (userinput == "help") {            //�L���O�C��
            help();
        }

        else if (userinput == "cls") {            //�M��
            clear();
        }

        else if (userinput == "exit") {
            judge = FALSE;
        }

        else cout << "error\n";

    }
    return EXIT_SUCCESS;
}

//���U�s���|��
string enroll_member(string name_member, string email_member, string password_member) {
    try
    {
        http::Request request{ "http://140.113.213.57:5125/enroll_member" };
        const string body = "{\"name_member\": \"" + name_member + "\", \"email_member\": \"" + email_member + "\", \"password_member\": \"" + password_member + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        cout << "_id= " << string{ response.body.begin(), response.body.end() } << '\n'; // print the result
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}

//�n�J�w�����|���b��
string login_member(string email_member, string password_member) {
    try
    {
        http::Request request{ "http://140.113.213.57:5125/login_member" };
        const string body = "{\"email_member\": \"" + email_member + "\", \"password_member\": \"" + password_member + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        cout << "_id= " << string{ response.body.begin(), response.body.end() } << '\n'; // print the result
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}

//�x�Ȩ�{���b��
int store_balance(string _id, int balance_member) {

    string balance = to_string(balance_member);
    try
    {
        http::Request request{ "http://140.113.213.57:5125/store_balance" };
        const string body = "{\"_id\": \"" + _id + "\", \"balance_member\": \"" + balance + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        cout << "balance= " << string{ response.body.begin(), response.body.end() } << '\n'; // print the result
        return stoi(string{ response.body.begin(), response.body.end() });
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }

    return -1;
}

//�W�ǰӫ~���
string upload_commodity(string _id_seller, string name_commodity, int price, int inventory) {
    string pricestr = to_string(price);
    string inventorystr = to_string(inventory);
    try
    {
        http::Request request{ "http://140.113.213.57:5125/upload_commodity" };
        const string body = "{\"_id_seller\": \"" + _id_seller + "\", \"name_commodity\": \"" + name_commodity + "\", \"price\": \"" + pricestr + "\", \"inventory\": \"" + inventorystr + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        cout << "_id= " << string{ response.body.begin(), response.body.end() } << '\n'; // print the result
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}

//�d�ݰӫ~�C��
string view_commodity() {
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

//B�VA�ʶR�ӫ~
string buy_commodity(string _id_buyer, string _id_seller, string _id_commdity, int number) {
    string numberstr = to_string(number);
    try
    {
        http::Request request{ "http://140.113.213.57:5125/buy_commodity" };
        const string body = "{\"_id_buyer\": \"" + _id_buyer + "\", \"_id_seller\": \"" + _id_seller + "\", \"_id_commdity\": \"" + _id_commdity + "\", \"number\": \"" + numberstr + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        cout << "_id= " << string{ response.body.begin(), response.body.end() } << '\n'; // print the result
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << "Request failed, error: " << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}

//���ѨϥΪ̫��O�C��
void help() {
    cout << "Input enroll can register account" << endl;
    cout << "Input logout can logout account" << endl;
    cout << "Input money  can store money in to your account" << endl;
    cout << "Input sell to  enter the seller mode" << endl;
    cout << "Input view to view all commodity" << endl;
    cout << "Input buy to  enter the buyer mode" << endl;
    cout << "Input cls to clear screen" << endl;
    cout << "Input exit to exit program" << endl;
}

//�M��
void clear() {
    system("cls");
}

//�e�m�B�z
void preprocessing(string& user_id) {
    string decide;
    cout << "Do you already have an account?" << endl;
    cout << "Please input Y/N" << endl;
    cin >> decide;

    if (decide == "N") {                //�бb��
        string user_name, user_email, passwd;
        cout << "Input your user name: ";
        cin >> user_name;
        cout << "Input your email account: ";
        cin >> user_email;
        cout << "Input your password: ";
        cin >> passwd;
        user_id = enroll_member(user_name, user_email, passwd); //�Ыرb���ño��user_id
    }
    else if (decide == "Y") {          //�n�J
        string intput_email, input_passwd;
        cout << "Input your email account: ";
        cin >> intput_email;
        cout << "Input your password: ";
        cin >> input_passwd;
        user_id = login_member(intput_email, input_passwd); //�n�J�ño��Member
    }
}