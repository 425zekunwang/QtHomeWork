#include "sell.h"
#include "ui_sell.h"
#include"QSqlQuery"
#include"QMessageBox"
sell::sell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sell)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec("select name from goods");//加载已有的商品
    while(query.next())
    {
     ui->comboBox->addItem(query.value(0).toString());
    }
}

sell::~sell()
{
    delete ui;
}

void sell::on_pushButton_clicked()
{
    int pieces=ui->lineEdit->text().toInt();//获取当前要售出的件数
    if(pieces<=0)
    {
        QMessageBox *err=new QMessageBox();
        err->setWindowTitle("错误");
        err->setText("不能售出负数");
        err->show();
    }
    else
    {
        QSqlQuery query;
        query.exec(QString("select inventory from goods where name=='%1'").arg( ui->comboBox->currentText()));
        query.next();
        int inventory=query.value(0).toInt();
        if(inventory<pieces)
        {
            QMessageBox *err=new QMessageBox();
            err->setWindowTitle("错误");
            err->setText("库存不足");
            err->show();
            return ;
        }
        else if(inventory==pieces)
        {
            //正好售完，删除库存的记录
            query.exec(QString("update goods set inventory=0 where name=='%1'").arg(ui->comboBox->currentText()));
            query.exec(QString("insert into sold(name,price,producer,pieces) select name,price,producer,inventory from goods);"));
        }
        else
        {
            //减少库存
            query.exec(QString("update goods set inventory='%1' where name=='%2'").arg(inventory-pieces).arg(ui->comboBox->currentText()));
            query.exec(QString("select pieces from sold where name=='%1'").arg(ui->comboBox->currentText()));
            query.next();
            int record_sold=query.value(0).toInt();
            query.exec(QString("update sold set pieces='%1' where name=='%2'").arg(pieces+record_sold).arg(ui->comboBox->currentText()));
        }
        emit send_sell();
        QMessageBox *err=new QMessageBox();
        err->setWindowTitle("售出");
        err->setText(ui->comboBox->currentText()+QString("出售了:%1").arg(pieces)+"件");
        err->show();
    }
}
