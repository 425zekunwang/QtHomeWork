#include "addmarket.h"
#include "ui_addmarket.h"
addMarket::addMarket(QWidget *parent) ://构造函数
    QWidget(parent),
    ui(new Ui::addMarket)
{
    ui->setupUi(this);
}

addMarket::~addMarket()//析构函数，释放内存
{
    delete ui;
}

void addMarket::on_pushButton_clicked()//添加账套，信号槽机制
{
    emit sendData(ui->lineEdit->text());
}
