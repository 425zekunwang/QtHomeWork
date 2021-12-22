#include "ctrl_admin.h"
#include "ui_ctrl_admin.h"
#include "mainsystem.h"
#include"add_admin.h"

#include<QSqlDatabase>
#include<QSqlQuery>
#include"qdebug.h"
extern QSqlDatabase database;

ctrl_admin::ctrl_admin(QWidget *parent) ://构造函数
    QWidget(parent),
    ui(new Ui::ctrl_admin)
{
    ui->setupUi(this);    
    QSqlQuery query;
    query.exec("select name from admin");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }
}

ctrl_admin::~ctrl_admin()//析构函数，释放内存
{
    delete ui;
}

void ctrl_admin::on_pushButton_clicked()//新增用户
{
    add_admin *add_admin_ui=new add_admin();
    connect(add_admin_ui,SIGNAL(senddata(bool)),this,SLOT(receivedata(bool)));
    //发射信号代表新增了用户后刷新当前数据
    add_admin_ui->show();
}

void ctrl_admin::on_pushButton_2_clicked() //删除用户
{
    QString to_del_admin=ui->comboBox->currentText();
    ui->comboBox->removeItem(ui->comboBox->currentIndex());

    QSqlQuery query;
    query.exec(QString("delete from admin where name='%1';").arg(to_del_admin));
}

void ctrl_admin::on_pushButton_3_clicked()//点击添加后弹出添加用户的操作界面
{
    close();
    MainSystem *mainsystem=new MainSystem();
    mainsystem->show();
}


void ctrl_admin::on_pushButton_4_clicked()
{
    ui->comboBox->clear();
    update_current();
}

void ctrl_admin::receivedata(bool flag)
{
    if(flag)//更新下拉框的账户
    {
        ui->comboBox->clear();
        update_current();
    }
}
void ctrl_admin::update_current()
{
    QSqlQuery query;
    query.exec("select name from admin");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }
}
