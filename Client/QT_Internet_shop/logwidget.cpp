#include "logwidget.h"
#include "ui_logwidget.h"
#include"mainwindow.h"
using namespace std;

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);

    func_init();

}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::func_init()
{

                                                                        // 觸發登入按钮的信號槽連接
    connect(ui->btn_log,SIGNAL(clicked()),this,SLOT(btn_log_clicked()));
                                                                        // 發出信號後關閉登入窗口的信號槽連接
    connect(this,SIGNAL(close_window()),this,SLOT(close()));
                                                                        // 觸發信號後與切換頁面函式連接
    connect(ui->btn_sign,&QPushButton::clicked,this,&LogWidget::switchPage);
    connect(ui->btn_check,&QPushButton::clicked,this,&LogWidget::switchPage);
    connect(ui->btn_back,&QPushButton::clicked,this,&LogWidget::switchPage);

    ui->edit_pw->setEchoMode(QLineEdit::Password);
}


void LogWidget::btn_log_clicked()                                       // 登入帳號
{
    qm_email = ui->edit_name->text();
    qm_password = ui->edit_pw->text();
    m_email=qm_email.toStdString();
    m_password=qm_password.toStdString();

    setEmail(m_email);
    string s="",u="";
                                                                        // 從伺服器取userid並字串分割
    int ss;
    s=login_member(m_email, m_password);
    ss=s.length();
    for(int  i=0;i < ss ; i++){
        if(s[i]!=','){
            u+=s[i];
        }
        else{
            break;
        }
    }
    setUid(u);                                                     // 登入並得到Member
    setMoney(store_balance(getUid(), 0));
    if (getUid()=="LOGIN FAILED:PASSWORD ERROR")

        QMessageBox::information(this, "Warning","密碼錯誤!");

    else if(getUid()=="LOGIN FAILED:NO SUCH EMAIL HAS ENROLLED")

        QMessageBox::information(this, "Warning","你輸入的電子郵件地址並未與帳號連結!");

    else {
        emit(login());
        emit(close_window());
        ui->edit_pw->clear();
        ui->edit_name->clear();
        this->close();
    }
}

void LogWidget::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());        // 得到按下的按鈕的指針
    if(button==ui->btn_sign)
        ui->stack->setCurrentIndex(1);
    else if(button==ui->btn_check){                                    // 註冊帳號
            qm_email= ui->edit_email_sign->text();
            qm_password= ui->edit_pw_sign->text();
            qusername= ui->edit_username->text();
        if(ui->edit_email_sign->text()==""||ui->edit_pw_sign->text()==""||ui->edit_username->text()==""){
            QMessageBox::warning(this, "","使用者名稱、email或密碼欄不可為空白");
        }
        else {
            m_email = qm_email.toStdString();
            m_password = qm_password.toStdString();
            username = qusername.toStdString();

            setName(username);
            setEmail(m_email);
            setUid(enroll_member(username, m_email, m_password)); // 創建帳號並得到user_id
            setMoney(store_balance(getUid(), 0));
            QMessageBox::information(this, "","註冊成功！");
            ui->edit_pw_sign->clear();
            ui->edit_email_sign->clear();
            ui->stack->setCurrentIndex(0);
        }
    }
    else if(button==ui->btn_back)
        ui->stack->setCurrentIndex(0);
}
string LogWidget::enroll_member(string name_member, string email_member, string password_member) {
    try
    {
        http::Request request{ "http://140.113.213.57:5125/enroll_member" };
        const string body = "{\"name_member\": \"" + name_member + "\", \"email_member\": \"" + email_member + "\", \"password_member\": \"" + password_member + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}



string LogWidget::login_member(string email_member, string password_member) {
    try
    {
        http::Request request{ "http://140.113.213.57:5125/login_member" };
        const string body = "{\"email_member\": \"" + email_member + "\", \"password_member\": \"" + password_member + "\"}";
        const auto response = request.send("POST", body, {
            {"Content-Type", "application/json"}
            });
        return string{ response.body.begin(), response.body.end() };
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return "ERROR:ENROLL NEW MEMBER ACCOUNT FAILED!";
}

