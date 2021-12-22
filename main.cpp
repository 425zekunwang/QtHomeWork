#include "mainwindow.h"

#include <QApplication>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QDebug>
int main(int argc, char *argv[])//主函数，入口
{
    QApplication a(argc, argv);
    MainWindow w;

        w.show();
    return a.exec();
}
