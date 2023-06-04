#include"Commodity_List.h"

CommodityList::CommodityList(string deal_with_string) {

    vector<string> goods = firstSpilitCommosity(deal_with_string);
	this->listLength = goods.size();
	this->commodityList = (Commodity*)NULL;

	Commodity* list = new Commodity[this->listLength];
	for (int i = 0; i < this->listLength; i++) {
		Commodity temporary_use = Commodity(goods[i]);
		list[i] = temporary_use;
	}
    
	this->commodityList = list;
}

//�I�s�ӫ~�C��
void CommodityList::viewCommodites() {
	cout << this->splitLine << endl;
	cout << "| num | commodity |   price   | inventory |" << endl;
	cout << this->splitLine << endl;
	for (int i = 0; i < this->listLength; i++) {
		this->commodityList[i].viewCommodity(i + 1);
		cout << this->splitLine << endl;
	}
	
}

//�r�����
const vector<string> CommodityList::split(const string& str, const string& pattern) {
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

//�ӫ~�C��:�@������
const vector<string> CommodityList::firstSpilitCommosity(string& str) {
    string pattern = ":";
    vector<string> ret = split(str, pattern);

    return ret;
}

//��o�ӫ~ID
string CommodityList::viewCommodityId(int i) const{
    return commodityList[i-1].getCommodityId();
}

//��o��aID
string CommodityList::viewSellerId(int i) const {
    return commodityList[i-1].getSellerId();
}

//��o����
int CommodityList::viewPrice(int i) const {
    return commodityList[i-1].getPrice();
}

//��o�ƶq
int CommodityList::viewInventory(int i) const {
    return commodityList[i-1].getInventory();
}