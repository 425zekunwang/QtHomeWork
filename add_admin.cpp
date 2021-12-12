#include "add_admin.h"
#include "ui_add_admin.h"
#include"QMessageBox"
#include"QSqlQuery"
#include"QSqlDatabase"
#include"QDateTime"
extern QSqlDatabase database;

add_admin::add_admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_admin)
{
    ui->setupUi(this);
}

add_admin::~add_admin()
{
    delete ui;
}

void add_admin::on_buttonBox_accepted()
{
    QString name=ui->lineEdit->text();
    QString code=ui->lineEdit_2->text();
    if(name=="" | code=="")
    {
        QMessageBox err;
        err.setWindowTitle("非法输入");
        err.setText("输入的用户名或者密码为空");
        err.show();
    }
    else
    {
        QSqlQuery query;
        QDateTime dataTime;
        QString order="insert into admin(name,pwd) values('%1','%2');";
        order=order.arg(name).arg(code);

        query.exec(order);
        query.next();
        query.finish();

        QMessageBox add_ok;
        add_ok.setText("用户"+name+"添加成功");
        add_ok.setWindowTitle("添加成功");
        add_ok.show();
        add_ok.exec();
        close();
    }
}
