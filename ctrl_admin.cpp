#include "ctrl_admin.h"
#include "ui_ctrl_admin.h"
#include "mainsystem.h"
#include"add_admin.h"

#include<QSqlDatabase>
#include<QSqlQuery>
#include"qdebug.h"
extern QSqlDatabase database;

ctrl_admin::ctrl_admin(QWidget *parent) :
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

ctrl_admin::~ctrl_admin()
{
    delete ui;
}

void ctrl_admin::on_pushButton_clicked()//新增用户
{
    add_admin *add_admin_ui=new add_admin();
    add_admin_ui->show();
}

void ctrl_admin::on_pushButton_2_clicked() //删除用户
{
    QString to_del_admin=ui->comboBox->currentText();
    ui->comboBox->removeItem(ui->comboBox->currentIndex());

    QSqlQuery query;
    query.exec(QString("delete from admin where name='%1';").arg(to_del_admin));
}

void ctrl_admin::on_pushButton_3_clicked()
{
    close();

    connect(ui->pushButton_3,SIGNAL(close_mainwindow()),this,SLOT(when_open_mainsystem()));
    MainSystem *mainsystem=new MainSystem();
    mainsystem->show();
}


void ctrl_admin::on_pushButton_4_clicked()
{
    ui->comboBox->clear();
    QSqlQuery query;
    query.exec("select name from admin");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }
}
