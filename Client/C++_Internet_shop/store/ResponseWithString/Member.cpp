#include"Member.h"
using namespace std;

Member::Member(string name, string email) {
	this->name = name;
	this->email = email;
}

string Member::getUid() const {
	return uid;
}

string Member::getName() const {
	return name;
}

string Member::getEmail() const {
	return email;
}

int Member::getMoney() const {
	return money;
}

void Member::setUid(string uid) {
	this->uid = uid;
}

void Member::setName(string name) {
	this->name = name;
}

void Member::setEmail(string email) {
	this->email = email;
}

void Member::setMoney(int money) {
	this->money = money;
}