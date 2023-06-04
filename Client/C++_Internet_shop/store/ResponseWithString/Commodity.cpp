#include"Commodity.h"

//���򳣤���  �t�XList��s
Commodity::Commodity() {
}

//���Ƨ@�B�z ��iData filed��
Commodity::Commodity(string process_data_string) {
    vector<string> acommodity = secondSpilitCommosity(process_data_string);
    this->commodity_id = acommodity[0];
    this->name_commodity = acommodity[1];
    this->seller_id = acommodity[2];
    this->price = stoi(acommodity[3]);
    this->inventory = stoi(acommodity[4]);
}

//�r�����
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

//�ӫ~�C��:�G������
const vector<string> Commodity::secondSpilitCommosity(string& str) {
    string pattern = ",";
    vector<string> ret = split(str, pattern);
    return ret;
}

//�L�ӫ~���
void Commodity::viewCommodity(int index) {
    cout << "| " << formatString(to_string(index), 4) <<
        "| " << formatString(this->name_commodity, 10) <<
        "| " << formatString(to_string(this->price), 10) <<
        "| " << formatString(to_string(this->inventory), 10) <<
        "|" << endl;
}

//�L�X�Ӫ��榡
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

//��o�ӫ~ID
string Commodity::getCommodityId() const {
    return this->commodity_id;
}

//��o��aID
string Commodity::getSellerId() const {
    return this->seller_id;
}

//��o����
int Commodity::getPrice() const {
    return this->price;
}

//��o�ƶq
int Commodity::getInventory() const {
    return this->inventory;
}