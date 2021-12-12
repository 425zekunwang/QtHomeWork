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

    query.exec(QString("insert into goods(name,price,inventory) values('%1','%2','%3');").arg(name).arg(price).arg(inventory));

    QMessageBox *tishi=new QMessageBox();
    tishi->setText("添加成功");
    tishi->show();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}
