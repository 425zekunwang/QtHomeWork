#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QSqlDatabase database;
QSqlQuery curd;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QSQLITE");
//    qDebug()<<QApplication::applicationDirPath();
    database.setDatabaseName("qt.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        ui->label_6->setText("数据库已连接");

        QSqlQuery query_markarket;
        query_markarket.exec("select * from surpermarket");
        if(!query_markarket.exec())
        {
            qDebug()<<"查询错误"<<query_markarket.lastError();
        }
        else
        {
            while(query_markarket.next())
            {

                ui->comboBox->addItem(query_markarket.value(1).toString());
                qDebug()<<query_markarket.value(1).toString();
            }
        }

        qDebug() << "Succeed to connect database." ;
        query_markarket.finish();
    }
}
MainWindow::~MainWindow()
{
    database.close();
    delete ui;
}


void MainWindow::on_pushButton_3_clicked()
{
    close();
    log_in *LogIn=new log_in();
    LogIn->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString delmarket_name=ui->comboBox->currentText();
    ui->comboBox->removeItem(ui->comboBox->currentIndex());
    curd.exec(QString("delete from surpermarket where name='%1';").arg(delmarket_name));

}

void MainWindow::on_pushButton_clicked() //添加账套
{
    addMarket *newMarket=new addMarket();

    connect(newMarket,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
    newMarket->show();
}

void MainWindow::receiveData(QString data)
{
    QSqlQuery if_repeat;
    if_repeat.exec(QString("select count(name) from surpermarket where name='%1';").arg(data));
    if_repeat.next();

    if(if_repeat.value(0).toInt()==0)
    {
        ui->comboBox->addItem(data);
        if_repeat.exec(QString("insert into surpermarket values(%1,'%2');").arg(ui->comboBox->count()).arg(data));
        if(if_repeat.exec())
        {
            qDebug()<<"添加失败"<<if_repeat.lastError();//这里很奇怪
        }
        else
        {
            qDebug()<<"添加成功";
        }
    }
    else
    {
        QMessageBox err;
        err.setText("输入账套已存在");
        err.setWindowTitle("账套已存在");
        err.exec();
        err.show();
    }
    if_repeat.finish();
}

