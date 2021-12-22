#include "file_reg.h"
#include "ui_file_reg.h"

file_reg::file_reg(QWidget *parent) ://构造函数
    QWidget(parent),
    ui(new Ui::file_reg)
{
    ui->setupUi(this);
}

file_reg::~file_reg()//析构函数，释放内存
{
    delete ui;
}
