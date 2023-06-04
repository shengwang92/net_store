#ifndef member_h
#define member_h
#include<string>
using namespace std;

class Member {
private:
    string uid, name, email;
    int money;
public:
    Member(string = "s", string = "s");
    string getUid() const;
    string getName() const;
    string getEmail() const;
    int getMoney() const;
    void setUid(string);
    void setName(string);
    void setEmail(string);
    void setMoney(int);

};
#endif