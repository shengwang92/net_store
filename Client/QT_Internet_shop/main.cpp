#include "mainwindow.h"
#include "member.h"
#include "logwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.Logwidget();
    return a.exec();
}
