#include "file_reg.h"
#include "ui_file_reg.h"

file_reg::file_reg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::file_reg)
{
    ui->setupUi(this);
}

file_reg::~file_reg()
{
    delete ui;
}
