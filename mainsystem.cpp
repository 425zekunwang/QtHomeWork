#include "mainsystem.h"
#include "ui_mainsystem.h"
#include"mainwindow.h"
#include"addgoods.h"

QList<goods> record;
MainSystem::MainSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSystem)
{
    ui->setupUi(this);

    record.clear();

    ui->tableWidget->clearContents();
    ui->tableWidget->update();
    QSqlQuery query;
    query.exec("select name,price,discount,inventory from goods;");
    while(query.next())
    {
        goods tmp={query.value(0).toString(),query.value(1).toFloat(),query.value(2).toFloat(),(unsigned)query.value(3).toInt()};
        record<<tmp;
    }
    ui->tableWidget->setRowCount(record.count());
    for(int i=0;i<record.length();i++)
    {
        int col=0;
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].inventory)));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(record[i].name));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].discount)));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].price)));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].discount*record[i].price)));
    }
}

MainSystem::~MainSystem()
{
    delete ui;
}

void MainSystem::on_pushButton_8_clicked()
{
    destroy();
    log_in *login=new log_in();
    login->show();
}

void MainSystem::on_pushButton_2_clicked()
{
    QLabel *extra=new QLabel();
    extra->setMinimumSize(160,240);
    extra->setText("小组成员：\n\t王泽坤\n\t刘承军\t陈文超\n\t文档制作:黄飞霞");
    extra->show();
}

void MainSystem::on_pushButton_9_clicked()
{
    close();
    MainWindow *mainwindow=new MainWindow();
    mainwindow->show();
}

void MainSystem::on_pushButton_7_clicked()//添加库存
{
    addgoods *addGoods=new addgoods();
    addGoods->show();
}
