#include "addmarket.h"
#include "ui_addmarket.h"
addMarket::addMarket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addMarket)
{
    ui->setupUi(this);
}

addMarket::~addMarket()
{
    delete ui;
}

void addMarket::on_pushButton_clicked()
{
    emit sendData(ui->lineEdit->text());
}
