#ifndef LOGWIDGET_H
#define LOGWIDGET_H
#include <string>
#include <QWidget>
#include <QMessageBox>
#include <string>
#include <iostream>
#include"HTTPRequest.h"
#include"member.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

namespace Ui {
class LogWidget ;
}

struct fileSturct;
class LogWidget : public QWidget,public member
{
    Q_OBJECT

public:
    explicit LogWidget(QWidget *parent = nullptr);
    ~LogWidget();

    void func_init(); //功能初始化
    void switchPage();//切換函數
    string login_member(string , string );
    string enroll_member(string , string , string );

signals:
    void login(); //登入主界面信號
    void close_window();  //關閉登入界面信號

public slots:
    void btn_log_clicked();  //登入按钮按下後觸發的事件
private:
    Ui::LogWidget *ui;
    QString qm_email;
    QString qm_password;
    QString qusername;
    string m_email,m_password,username;

};
#endif // LOGWIDGET_H
