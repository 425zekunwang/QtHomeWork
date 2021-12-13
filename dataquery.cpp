#include "dataquery.h"
#include "ui_dataquery.h"

dataQuery::dataQuery(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dataQuery)
{
    ui->setupUi(this);
}

dataQuery::~dataQuery()
{
    delete ui;
}
