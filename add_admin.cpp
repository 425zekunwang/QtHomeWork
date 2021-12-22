#include "add_admin.h"
#include "ui_add_admin.h"
#include"QMessageBox"
#include"QSqlQuery"
#include"QSqlDatabase"
#include"QDateTime"
extern QSqlDatabase database;

add_admin::add_admin(QWidget *parent) ://构造函数
    QWidget(parent),
    ui(new Ui::add_admin)
{
    ui->setupUi(this);
}

add_admin::~add_admin()//析构函数，释放内存
{
    delete ui;
}

void add_admin::on_buttonBox_accepted()//点击添加账户后
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
        QString order="insert into admin(name,pwd) values('%1','%2');";
        order=order.arg(name).arg(code);

        query.exec(order);
        //使指针指向下一个有效指针
        query.next();

        QMessageBox add_ok;
        add_ok.setText("用户"+name+"添加成功");
        add_ok.setWindowTitle("添加成功");
        add_ok.show();//展示
        add_ok.exec();
        emit senddata(true);//发射信号
        close();
    }
}
