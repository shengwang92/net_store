#ifndef CommodityList_H
#define CommodityList_H

#include <vector>
#include <string>
#include "Commodity.h"
using namespace std;

class CommodityList {
private:
    Commodity* commodityList;
    int listLength = 0;
    string splitLine = "-------------------------------------------";

    
public:
    CommodityList(string deal_with_string);
    void viewCommodites();
    const vector<string> split(const string&, const string&);      //�r�����
    const vector<string> firstSpilitCommosity(string&);            //�ӫ~�C��:�@������
    string viewCommodityId(int) const;
    string viewSellerId(int) const;
    int viewPrice(int) const;
    int viewInventory(int) const;

};
#endif
#pragma once