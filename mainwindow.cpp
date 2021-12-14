#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QSqlDatabase database;

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


void MainWindow::on_pushButton_3_clicked()//点击下一步
{
    close();
    log_in *LogIn=new log_in();
    LogIn->show();
}

void MainWindow::on_pushButton_4_clicked()//退出按钮
{
    close();
}

void MainWindow::on_pushButton_2_clicked()//
{
    QSqlQuery curd;
    QString delmarket_name=ui->comboBox->currentText();
    ui->comboBox->removeItem(ui->comboBox->currentIndex());
    curd.exec(QString("delete from surpermarket where name=='%1';").arg(delmarket_name));

}

void MainWindow::on_pushButton_clicked() //添加账套
{
    addMarket *newMarket=new addMarket();
    //发射信号当添加了账套后，就会在主界面的下拉框中增加一个企业
    connect(newMarket,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));
    newMarket->show();
}

void MainWindow::receiveData(QString data)
{
    QSqlQuery if_repeat;
    if_repeat.exec(QString("select count(name) from surpermarket where name=='%1';").arg(data));
    if_repeat.next();
    //在QSqlQuery类中当执行exec()后会把指针放在记录集中第一个记录之上

    if(if_repeat.value(0).toInt()==0)//如果发现数据库中的记录为零则添加一个
    {
        ui->comboBox->addItem(data);
        if_repeat.exec(QString("insert into surpermarket(name) values('%1');").arg(data));
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
    //该函数通常无需调用，除非同一QSqlQuery对象间隔一段时间再使用时，调用该函数可释放资源。
}

