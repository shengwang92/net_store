#include"Commodity.h"

//什麼都不做  配合List刷新
Commodity::Commodity() {
}

//對資料作處理 放進Data filed中
Commodity::Commodity(string process_data_string) {
    vector<string> acommodity = secondSpilitCommosity(process_data_string);
    this->commodity_id = acommodity[0];
    this->name_commodity = acommodity[1];
    this->seller_id = acommodity[2];
    this->price = stoi(acommodity[3]);
    this->inventory = stoi(acommodity[4]);
}

//字串分割
const vector<string> Commodity::split(const string& str, const string& pattern) {
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

//商品列表:二次分割
const vector<string> Commodity::secondSpilitCommosity(string& str) {
    string pattern = ",";
    vector<string> ret = split(str, pattern);
    return ret;
}

//印商品表格
void Commodity::viewCommodity(int index) {
    cout << "| " << formatString(to_string(index), 4) <<
        "| " << formatString(this->name_commodity, 10) <<
        "| " << formatString(to_string(this->price), 10) <<
        "| " << formatString(to_string(this->inventory), 10) <<
        "|" << endl;
}

//印出來的格式
string Commodity::formatString(string param, int length)
{
    int strlength;
    char* output_array = new char[length + 1];
    string ret;

    strlength = param.length();
    const char* char_array = param.c_str();
    
    for (int i = 0; i < length; i++)
        if (i < strlength)
            output_array[i] = char_array[i];
        else
            output_array[i] = ' ';
    output_array[length] = '\0';
    ret = output_array;

    return ret;
}

//獲得商品ID
string Commodity::getCommodityId() const {
    return this->commodity_id;
}

//獲得賣家ID
string Commodity::getSellerId() const {
    return this->seller_id;
}

//獲得價錢
int Commodity::getPrice() const {
    return this->price;
}

//獲得數量
int Commodity::getInventory() const {
    return this->inventory;
}