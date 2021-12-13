#include "addgoods.h"
#include "ui_addgoods.h"
#include<QSqlQuery>
#include"QMessageBox"

addgoods::addgoods(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addgoods)
{
    ui->setupUi(this);
}

addgoods::~addgoods()
{
    delete ui;
}

void addgoods::on_pushButton_clicked()
{
    QSqlQuery query;

    QString name=ui->lineEdit->text();
    float price=(ui->lineEdit_2->text()).toFloat();
    unsigned inventory=(ui->lineEdit_3->text()).toInt();
    QString producer=(ui->lineEdit_4->text());

    QMessageBox *tishi=new QMessageBox();

    query.exec(QString("select count(name) from goods where name=='%1';").arg(name));
    query.next();
    if(query.value(0).toInt()>0)
    {
        query.exec(QString("select inventory from goods where name=='%1';").arg(name));
        query.next();
        unsigned old=query.value(0).toInt();
        query.exec(QString("update goods set inventory='%1' where name=='%2';").arg(old+inventory).arg(name));

        tishi->setText("添加已有商品成功！");
        tishi->show();
    }
    else
    {
    query.exec(QString("insert into goods(name,price,inventory,producer) values('%1','%2','%3','%4');").arg(name).arg(price).arg(inventory).arg(producer));
    tishi->setText("添加新的商品成功!");
    tishi->show();
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}
