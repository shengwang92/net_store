#!flask/bin/python
from flask import Flask, jsonify, request
app = Flask(__name__)

import logging
import os
import datetime
import pandas as pd

FORMAT = '%(asctime)s,%(levelname)s,%(message)s'
DATE_FORMAT = '%Y/%m/%d,%H:%M:%S'
logging.warning("Start Server")
logging.basicConfig(level=logging.INFO, filename='mall.log', filemode='w',
	format='[%(asctime)s %(levelname)-8s] %(message)s',
	datefmt='%Y%m%d %H:%M:%S',
	)

ISOTIMEFORMAT = '%Y/%m/%d,%H:%M:%S'

logger = logging.getLogger()
logger.setLevel(logging.INFO)
formatter = logging.Formatter(
	'[%(levelname)1.1s %(asctime)s %(module)s:%(lineno)d] %(message)s',
	datefmt='%Y%m%d %H:%M:%S')

streamhandler = logging.StreamHandler()
streamhandler.setLevel(logging.INFO)
streamhandler.setFormatter(formatter)

filehandler = logging.FileHandler('mall.log')
filehandler.setLevel(logging.INFO)
filehandler.setFormatter(formatter)

logger.addHandler(streamhandler)
logger.addHandler(filehandler)

import csv
import uuid
from datetime import datetime

#讀取會員資料
def read_data_member():
    data_member=[]
    with open('./data_member.csv', newline='') as datbase_member:
        members = csv.reader(datbase_member)
        for member in members:
            data_member.append(member)
        datbase_member.close()
    return data_member

#寫入會員資料
def write_data_member(data):
    with open('./data_member.csv', 'w', newline='') as datbase_member:
        writer = csv.writer(datbase_member)
        writer.writerows(data)
        datbase_member.close()

#讀取商品資料
def read_data_commodity():
    data_commodity=[]
    with open('./data_commodity.csv', newline='') as datbase_commodity:
        commoditys = csv.reader(datbase_commodity)
        for commodity in commoditys:
            data_commodity.append(commodity)
        datbase_commodity.close()
    return data_commodity

#寫入商品資料
def write_data_commodity(data):
    with open('./data_commodity.csv', 'w', newline='') as datbase_commodity:
        writer = csv.writer(datbase_commodity)
        writer.writerows(data)
        datbase_commodity.close()

#找尋對應會員資料
def find_member(_id):
    database_member=pd.read_csv('data_member.csv')
    index=-1
    for ind,val in enumerate(database_member['_id']):
        if(str(val)==_id):
            index=ind
    if(index==-1):
        logging.info("FAILED:CANNOT FIND MEMBER")
        return -1
    member=database_member.values.tolist()[index]
    return {"_id":member[0],
            "name_member":member[1],
            "date_enrolled":member[2],
            "email_member":member[3],
            "password_member":member[4],
            "balance_member":member[5]}

#更新餘額
def update_balance_member(_id,variance):
    member=find_member(_id)
    if(member==-1):
        return "FAILED:CANNOT FIND MEMBER"
    
    #清除舊資料
    old_data=read_data_member()
    old_index=-1
    for ind,val in enumerate(old_data):
        if(val[0]==str(_id)):
            old_index=ind
    if(old_index==-1):
        print("ERROR:CANNOT FIND INDEX")
        logging.debug("ERROR:CANNOT FIND INDEX")
    old_data.pop(old_index)
    
    #更新新資料
    new_balance=int(member['balance_member'])+variance
    old_data.append([
        _id,
        member['name_member'],
        member['date_enrolled'],
        member['email_member'],
        member['password_member'],
        new_balance
    ])
    new_data=old_data
    write_data_member(new_data)

#找尋對應商品資料
def find_commodity(_id):
    database_commodity=pd.read_csv('data_commodity.csv')
    index=-1
    for ind,val in enumerate(database_commodity['_id']):
        if(str(val)==_id):
            index=ind
    if(index==-1):
        logging.info("FAILED:CANNOT FIND COMMODITY")
        return -1
    commodity=database_commodity.values.tolist()[index]
    return {"_id":commodity[0],
            "name_commodity":commodity[1],
            "_id_seller":commodity[2],
            "price":commodity[3],
            "inventory":commodity[4]}

#更新商品庫存
def update_inventory_commodity(_id,variance):
    commodity=find_commodity(_id)
    if(commodity==-1):
        return "FAILED:CANNOT FIND COMMODITY"
    
    #清除舊資料
    old_data=read_data_commodity()
    old_index=-1
    for ind,val in enumerate(old_data):
        if(val[0]==str(_id)):
            old_index=ind
    if(old_index==-1):
        print("ERROR:CANNOT FIND INDEX")
        logging.debug("ERROR:CANNOT FIND INDEX")
    old_data.pop(old_index)
    
    #更新新資料
    new_inventory=int(commodity['inventory'])-variance
    if(new_inventory<=0):
        new_data=old_data
        write_data_commodity(new_data)
        return
    old_data.append([
        _id,
        commodity['name_commodity'],
        commodity['_id_seller'],
        commodity['price'],
        new_inventory
    ])
    new_data=old_data
    write_data_commodity(new_data)

#GET測試
@app.route('/get_test' , methods=['GET'])
def get_test():
    logging.info("GET TEST REQUEST")
    return "GET TEST REQUEST"

#POST
@app.route('/post_test' , methods=['POST'])
def post_test():
    request_data = request.get_json()
    return jsonify(request_data)

#還原資料庫
@app.route('/clear_database' , methods=['GET'])
def clear_database():
    init_data_member = [['_id', 'name_member', 'date_enrolled','email_member','password_member','balance_member']]
    write_data_member(init_data_member)
    logging.info("Init member database")
    init_data_commodity = [['_id','name_commodity', '_id_seller', 'price','inventory']]
    write_data_commodity(init_data_commodity)
    logging.info("Init commodity database")
    return "SUCCESS"
        
#註冊會員
@app.route('/enroll_member' , methods=['POST'])
def enroll_member():
    request_data = request.get_json()
    _id=uuid.uuid1().hex
    new_member=[
        _id,
        request_data['name_member'],
        datetime.now().strftime("%Y%m%d %H:%M:%S"),
        request_data['email_member'],
        request_data['password_member'],
        0
    ]
    data_members=read_data_member()
    #確認是否已經存在相同帳號
    frame=pd.DataFrame(data_members[1:],columns =['_id', 'name_member', 'date_enrolled', 'email_member', 'password_member', 'balance_member'])
    if(request_data['email_member'] in list(frame['email_member'])):
        return "ENROLL FAILED: EMAIL: "+str(request_data['email_member'])+" HAS BEEN ENROLLED!"
    #確認是否有
    data_members.append(new_member)
    write_data_member(data_members)
    logging.info("Enroll A New Member "+_id)
    return str(_id)

#登入會員
@app.route('/login_member' , methods=['POST'])
def login_member():
    request_data = request.get_json()
    print(str(request_data))
    logging.info("Data: "+str(request_data))
    database_member=pd.read_csv('data_member.csv')
    #搜尋有沒有該帳號
    index=-1
    for ind,val in enumerate(database_member['email_member']):
        if(str(val)==request_data['email_member']):
            index=ind
    if(index==-1):
        logging.info("LOGIN FAILED:NO SUCH EMAIL HAS ENROLLED")
        return "LOGIN FAILED:NO SUCH EMAIL HAS ENROLLED"
        
    member=database_member.values.tolist()[index]
    #檢查密碼是否相符
    if(str(member[4])==request_data['password_member']):
        logging.info("LOGIN SUCESS")
        retstring=""
        for i in member:
            retstring+=str(i)+","
        logging.info("Return: "+str(retstring[:-1]))
        return retstring[:-1]
    else:
        logging.info("LOGIN FAILED:PASSWORD ERROR")
        return "LOGIN FAILED:PASSWORD ERROR"

#儲值
@app.route('/store_balance' , methods=['POST'])
def store_balance():
    request_data = request.get_json()
    _id=request_data['_id']
    member=find_member(_id)
    logging.info("Data: "+str(request_data))
    if(member==-1):
        return "FAILED: UID IS INCORRECT"
    # #更新新資料
    new_balance=int(member['balance_member'])+int(request_data['balance_member'])
    update_balance_member(_id,int(request_data['balance_member']))
    logging.info("MEMBER "+_id+" STORE MONEY "+str(request_data['balance_member'])+" DOLLOR SUCCESS,TOTAL: "+str(new_balance))
    print("MEMBER "+_id+" STORE MONEY "+str(request_data['balance_member'])+" DOLLOR SUCCESS,TOTAL: "+str(new_balance))
    return str(new_balance)

#上傳商品
@app.route('/upload_commodity' , methods=['POST'])
def upload_commodity():
    request_data = request.get_json()
    _id=uuid.uuid1().hex
    data=read_data_commodity()
    data.append([
        _id,
        request_data['name_commodity'],
        request_data['_id_seller'],
        request_data['price'],
        request_data['inventory']
    ])
    write_data_commodity(data)
    logging.info("SUCESS UPLOAD COMMODITY: "+str(_id))
    return _id

#檢視商品
@app.route('/view_commodity' , methods=['GET'])
def view_commodity():
    logging.info("COMMODITY STORE HAS BEEN VIEWED")
    origindata=read_data_commodity()[1:]
    retstring=""
    for commoditys in origindata:
        tempstring=""
        for commodity in commoditys:
            tempstring+=str(commodity)+","
        retstring+=(tempstring[:-1]+":")
    print(retstring)
    return retstring

#購買商品
@app.route('/buy_commodity' , methods=['POST'])
def buy_commodity():
    request_data = request.get_json()
    _id_commdity=request_data['_id_commdity']
    
    #計算商品交易量
    commodity=find_commodity(_id_commdity)
    number=int(request_data['number'])
    total_tade=number*int(commodity['price'])
    
    #更新商品資料
    update_inventory_commodity(_id_commdity,number)
    logging.info("INVENTORY UPDATE COMMPLETE:TRADE "+str(number)+" , REMAINIG "+str(int(commodity['inventory'])-number))
    print("INVENTORY UPDATE COMMPLETE:TRADE "+str(number)+" , REMAINIG "+str(int(commodity['inventory'])-number))

    #更新買家餘額
    _id_buyer=request_data['_id_buyer']
    update_balance_member(_id_buyer,(-1)*total_tade)
    remaining_buyer=find_member(_id_buyer)['balance_member']
    logging.info("DEBIT SUCESS:TRADE "+str(total_tade)+", REMAINING "+str(remaining_buyer))
    print("DEBIT SUCESS:TRADE "+str(total_tade)+", REMAINING "+str(remaining_buyer))

    #更新賣家餘額
    _id_seller=request_data['_id_seller']
    update_balance_member(_id_seller,total_tade)
    remaining_seller=find_member(_id_seller)['balance_member']
    logging.info("TRADE SUCESS:TRADE "+str(total_tade)+", REMAINING "+str(remaining_seller))
    print("TRADE SUCESS:TRADE "+str(total_tade)+", REMAINING "+str(remaining_seller))
    return "SUCESS"


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True,port=5125)
