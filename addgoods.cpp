#include "addgoods.h"
#include "ui_addgoods.h"
#include<QSqlQuery>
#include"QMessageBox"
#include"QFile"
#include"QFileInfo"
#include"QTextStream"
#include"qDebug"
#include"QTextCodec"
addgoods::addgoods(QWidget *parent) ://构造函数
    QDialog(parent),
    ui(new Ui::addgoods)
{
    ui->setupUi(this);
}

addgoods::~addgoods()//析构函数，释放内存
{
    delete ui;
}

void addgoods::on_pushButton_clicked()//添加入库
{
    QSqlQuery query;
    //获取每个商品的信息
    QString name=ui->lineEdit->text();
    float price=(ui->lineEdit_2->text()).toFloat();
    unsigned inventory=(ui->lineEdit_3->text()).toInt();
    QString producer=(ui->lineEdit_4->text());

      //构造新的信息弹窗
    QMessageBox *tishi=new QMessageBox();

     //

    query.exec(QString("select count(name) from goods where name=='%1';").arg(name));
    //使指针指向下一个有效指针
    query.next();

    //添加商品，并进行判断
    if(query.value(0).toInt()>0)
    {
        query.exec(QString("select inventory from goods where name=='%1';").arg(name));
        query.next();
        unsigned old=query.value(0).toInt();
        query.exec(QString("update goods set inventory='%1' where name=='%2';").arg(old+inventory).arg(name));

        tishi->setText("添加已有商品成功！");
        tishi->show();
    }
    else
    {
    query.exec(QString("insert into goods(name,price,inventory,producer) values('%1','%2','%3','%4');").arg(name).arg(price).arg(inventory).arg(producer));
    tishi->setText("添加新的商品成功!");
    tishi->show();
    }
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    //
    emit sendsignal();
}

void addgoods::on_pushButton_2_clicked()//批量入库
{
    QSqlQuery query;
    //先打开文件
//    qDebug()<<QApplication::applicationDirPath();
    QFile file("Q:\\QtHomeWork-main\\build-QtHomeWork-Desktop_x86_windows_msys_pe_32bit-Debug\\debug\\invention\\statement.dat");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    //使用QTextStream一行一行读取文件
    QByteArray line;
    QMessageBox *tishi=new QMessageBox();
    //更改编码器
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    while (!file.atEnd())
    {

        line = file.readLine();      //整行读取

    //转换文件内容
        QString str=codec->toUnicode(line);
        qDebug()<<"line:"<<str;
        QStringList list = str.split(" ");
        QString name=list[0];
        QString price=list[1];
         QString inventory=list[2];
        QString producer=list[3];
        qDebug()<<name;
     query.exec(QString("insert into goods(name,price,inventory,producer) values('%1','%2','%3','%4');").arg(name).arg(price).arg(inventory).arg(producer));
     qDebug() << line;
    }

    //弹窗信息
    tishi->setText("批量入库成功!");
    tishi->show();

      file.close();
      // 发送信号，以更新显示界面
      emit xinhao();
}
