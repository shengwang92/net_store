#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commodity.h"
#include "member.h"
#include"HTTPRequest.h"
#include <vector>
#include <iostream>
#include <QDebug>
#include <QIntValidator>
#include<string>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

int MainWindow::pus = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
                                                                // 連結所有按鈕的信號
    connectbutton();
                                                                // 防呆，令使用者只能輸入int型別
    QIntValidator* int_validator = new QIntValidator();
    ui->edit_money->setValidator(int_validator);
    ui->edit_commodity_price->setValidator(int_validator);
    ui->edit_count->setValidator(int_validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_logout_clicked()                        // 登出
{

        QMessageBox messageBox(QMessageBox::NoIcon,"退出", "你確定要退出嗎?",
                               QMessageBox::Yes | QMessageBox::No, NULL);
        int result=messageBox.exec();
        switch (result)
        {
        case QMessageBox::Yes:
            qDebug()<<"Yes";
            this->close();
            m_log->show();
            break;
        case QMessageBox::No:
            qDebug()<<"NO";
            break;
        default:
            break;
        }

}
void MainWindow::commodity_list(){                              // 顯示商品介面
    string first = view_commodity();
    vector<string> goods=split(first,":");
    size=goods.size();
    commodity=(commodity1*)NULL;

    commodity=new commodity1[size];
    for(int i=0;i<size;i++){
        commodity[i]=commodity1(goods[i]);
    }


    if(p<size||p==2||p==1||p==0)
    {
        vector<QString> com;
        vector<int> pr,cnt;
        for(int i=0;i<size;i++){
            com.push_back(commodity[i].getcommodity());
            pr.push_back(commodity[i].getcommodity_price());
            cnt.push_back(commodity[i].getcount());
        }

        ui->label_com1->setText(com[p]);
        if(p+1<size)
            ui->label_com2->setText(com[p+1]);
        else
            ui->label_com2->clear();
        if(p+2<size)
            ui->label_com3->setText(com[p+2]);
        else
            ui->label_com3->clear();
        ui->label_pr1->setText(QString::number(pr[p]));
        if(p+1<size)
            ui->label_pr2->setText(QString::number(pr[p+1]));
        else
            ui->label_pr2->clear();
        if(p+2<size)
            ui->label_pr3->setText(QString::number(pr[p+2]));
        else
            ui->label_pr3->clear();
        ui->label_cnt1->setText(QString::number(cnt[p]));
        if(p+1<size)
            ui->label_cnt2->setText(QString::number(cnt[p+1]));
        else
            ui->label_cnt2->clear();
        if(p+2<size)
            ui->label_cnt3->setText(QString::number(cnt[p+2]));
        else
            ui->label_cnt3->clear();
    }
}
void MainWindow::show_commodity(){                              // 商品數據
    vector<QString> com;
    vector<int> pr,cnt;
    for(int i=0;i<size;i++){
        com.push_back(commodity[i].getcommodity());
        pr.push_back(commodity[i].getcommodity_price());
        cnt.push_back(commodity[i].getcount());
    }
    ui->label_com->setText("名稱："+(com[p+value-1]));
    ui->label_cnt->setText("數量："+QString::number(cnt[p+value-1]));
    ui->label_cpr->setText("價格："+QString::number(pr[p+value-1]));
}


void MainWindow::connectbutton(){                               // 連接按鈕
    connect(ui->btn_buy,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_money,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_sell,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_back_b,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_back_m,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_back_s,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_check_s,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_buy1,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_buy2,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_buy3,&QPushButton::clicked,this,&MainWindow::switchPage);
    connect(ui->btn_buypage_back,&QPushButton::clicked,this,&MainWindow::switchPage);
}
void MainWindow::switchPage(){                                  // 切換頁面
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button==ui->btn_buy){
        ui->stack->setCurrentIndex(3);
        if(pus==1){
           pus++;
        }
        page_reset();
        commodity_list();
    }
    else if(button==ui->btn_money){
        ui->edit_show_money->setText(QString::number(getMoney()));
        ui->stack->setCurrentIndex(1);
        ui->edit_show_money->setReadOnly(true);
    }
    else if(button==ui->btn_sell)
        ui->stack->setCurrentIndex(2);
    else if(button==ui->btn_back_b){
       ui->stack->setCurrentIndex(0);
       p=0;
    }
    else if(button==ui->btn_back_s){
        ui->stack->setCurrentIndex(0);
        sell_clear();
    }
    else if(button==ui->btn_buypage_back){
        ui->stack->setCurrentIndex(3);
        page_reset();
        ui->label_total->clear();
        ui->edit_commodity_price_2->clear();
    }
    else if(button==ui->btn_back_m)
        ui->stack->setCurrentIndex(0);
    else if(button==ui->btn_buy1){
        ui->stack->setCurrentIndex(4);
        value=1;
        show_commodity();
        print_money();
    }
    else if(button==ui->btn_buy2){
        if(ui->label_cnt2->text()!=""){
            ui->stack->setCurrentIndex(4);
            value=2;
            show_commodity();
            print_money();
        }
    }
    else if(button==ui->btn_buy3){
        if(ui->label_cnt3->text()!=""){
            ui->stack->setCurrentIndex(4);
            value=3;
            show_commodity();
            print_money();
        }
    }
}

void MainWindow::print_money(){
    ui->label_money_2->setText("我的金錢："+QString::number(getMoney()));
}

void MainWindow::sell_clear(){
    ui->edit_commodity->clear();
    ui->edit_commodity_price->clear();
    ui->edit_count->clear();
}

void MainWindow::page_reset(){
    ui->label_page->setText("目前頁面："+QString::number(p/3));
    ui->label_money->setText("我的金錢："+QString::number(getMoney()));
}

void MainWindow::on_btn_check_s_clicked()                       // 販賣商品
{
    QString com;
    int price,inventory;
    string commodity_id;
    if(ui->edit_commodity->text()==""||ui->edit_commodity_price->text()==""||ui->edit_count->text()=="")
    {
        QMessageBox::warning(this, "","商品數量、商品價格或商品名稱不可為空白！");
    }
    else{
        com = ui->edit_commodity->text();
        price = ui->edit_commodity_price->text().toInt();
        inventory = ui->edit_count->text().toInt();
        string commodity_name=com.toStdString();
        commodity_id = upload_commodity(getUid(), commodity_name, price, inventory);
        QMessageBox::information(this, "","新增商品成功！");
        ui->stack->setCurrentIndex(0);
        sell_clear();

    }
}

void MainWindow::on_btn_check_m_clicked()                       // 儲值
{
    int m;
    if(ui->edit_money->text()==""){
        QMessageBox::warning(this, "","金額不可為空白！");
    }
    else{
        m = ui->edit_money->text().toInt();
        setMoney(store_balance(getUid(), m));
        ui->edit_money->clear();
        ui->stack->setCurrentIndex(0);
        QMessageBox::information(this, "","儲值成功");
    }
}

void MainWindow::on_btn_next_clicked()                           // 商品頁面 下一頁
{
    if(p+3<size){
        p+=3;
        commodity_list();
        page_reset();
    }
    else
        QMessageBox::warning(this, "","最後一頁了！");
}

void MainWindow::on_btn_back_clicked()                           // 購買商品 上一頁
{
    if(p!=0){
        p-=3;
        page_reset();
        commodity_list();
    }
}

void MainWindow::on_btn_check_s_2_clicked()                      // 購買商品
{
    int pr,cnt;
    int input;
    cnt=commodity[p+value-1].getcount();
    pr=commodity[p+value-1].getcommodity_price();
    input=ui->edit_commodity_price_2->text().toInt();

    if(input>cnt)
        QMessageBox::warning(this, "","購買商品數量不可大於剩餘數量！");
    else if (getMoney()<pr*input){
        QMessageBox::warning(this, "","剩餘金錢不足以購買商品總額！");
    }
    else{
        string feasible = buy_commodity(getUid(), commodity[p+value-1].getSeller_id(), commodity[p+value-1].getCommodity_id(), input);
        if (feasible != "SUCESS"){
            QMessageBox::warning(this, "","購買失敗！請重新操作");
        }
        else{
            QMessageBox messageBox(QMessageBox::NoIcon,"購買", "確認購買嗎?",
                                   QMessageBox::Yes | QMessageBox::No, NULL);
            int result=messageBox.exec();
            switch (result)
            {
            case QMessageBox::Yes:
                qDebug()<<"Yes";
                ui->stack->setCurrentIndex(0);
                ui->edit_commodity_price_2->clear();
                QMessageBox::information(this, "","購買成功！");
                setMoney(store_balance(getUid(), 0));
                break;
            case QMessageBox::No:
                qDebug()<<"NO";
                break;
            default:
                break;
            }
        }

    }
}

const vector<string> MainWindow::split(const string& str, const string& pattern) {
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

void MainWindow::Logwidget(){                                   // 新增視窗

    // 通過指針創建登入界面類的對象
    m_log = new LogWidget;
    // 調用登入視窗的show()函數顯示登入介面
    m_log->show();
    // 建立信號槽到接收到登入介面發來的login()信號後，調用主窗口的show()函數。
    connect(m_log,SIGNAL(login()),this,SLOT(show()));
}

