#ifndef MainWindow_h
#define MainWindow_h
#include "logwidget.h"
#include "commodity.h"
#include "member.h"
#include<string>
using namespace std;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,public member
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void switchPage();//切換函數
    void connectbutton();
    void commodity_list();
    void sell_clear();
    void page_reset();
    void print_money();
    void show_commodity();
    void Logwidget();


private slots:
    void on_btn_logout_clicked();
    void on_btn_check_s_clicked();
    void on_btn_check_m_clicked();
    void on_btn_next_clicked();
    void on_btn_back_clicked();
    void on_btn_check_s_2_clicked();

private:
    Ui::MainWindow *ui;
    // 登入介面的對象作為指針
    LogWidget * m_log;
    commodity1 * commodity;
    static int pus;
    int p=0;
    int size;
    int value=0;

    const vector<string> split(const string&,const string&);
};

#endif // MAINWINDOW_H
