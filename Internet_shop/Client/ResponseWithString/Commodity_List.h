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
    const vector<string> split(const string&, const string&);      //字串分割
    const vector<string> firstSpilitCommosity(string&);            //商品列表:一次分割
    string viewCommodityId(int) const;
    string viewSellerId(int) const;
    int viewPrice(int) const;
    int viewInventory(int) const;

};
#endif
#pragma once