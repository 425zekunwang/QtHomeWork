#include "mainsystem.h"
#include "ui_mainsystem.h"
#include"mainwindow.h"
#include"addgoods.h"
#include"sell.h"

QList<goods> record;
bool if_mutiple=false;
QList<QPair<QString,QString>> mutiple_condition;
QMap<QString,QString> text_map={{"商品名称","name"},
                                {"商品售价","price"},
                                {"生产厂家","producer"},
                                {"商品库存","inventory"}};

MainSystem::MainSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSystem)
{
    ui->setupUi(this);
    ui->comboBox->hide();
    ui->pushButton_11->hide();
    ui->lineEdit->hide();
    ui->checkBox->hide();
    ui->pushButton_13->hide();
    ui->pushButton_12->hide();
    update_current();
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
    connect(addGoods,SIGNAL(sendsignal()),this,SLOT(update_current()));
    addGoods->show();
}

void MainSystem::on_pushButton_4_clicked()//勾选了数据查询
{

    ui->pushButton_13->show();

    ui->comboBox->show();
    ui->pushButton_11->show();
    ui->lineEdit->show();
    ui->checkBox->show();

    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
}

void MainSystem::update_current()
{
    record.clear();

    ui->tableWidget->clearContents();
    QSqlQuery query;
    query.exec("select name,price,discount,inventory,producer from goods;");
    while(query.next())
    {
        goods tmp={query.value(0).toString(),query.value(1).toFloat(),query.value(2).toFloat(),(unsigned)query.value(3).toInt(),query.value(4).toString()};
        record<<tmp;
    }
    show_data();
}
void MainSystem::update_query(QString text,QString order)
{
    record.clear();
    ui->tableWidget->clearContents();
    QSqlQuery query;
QString to_query=QString("select name,price,discount,inventory,producer from goods where %2=='%1';").arg(text).arg(order);
    query.exec(to_query);
    while(query.next())
    {
        goods tmp={query.value(0).toString(),query.value(1).toFloat(),query.value(2).toFloat(),(unsigned)query.value(3).toInt(),query.value(4).toString()};
        record<<tmp;
    }
    query.finish();
    show_data();
}
void MainSystem::on_pushButton_11_clicked()//点击查询的函数
{
    record.clear();
//    qDebug()<<"当前是"<<(if_mutiple?"多选":"单选")<<"模式";
    if(!if_mutiple)//单选模式
    {
        QString current_query_name=ui->comboBox->currentText();
        qDebug()<<"单选"<<ui->lineEdit->text()<<" "<<text_map[current_query_name];
        update_query(ui->lineEdit->text(),text_map[current_query_name]);
    }
    else//多选模式
    {
        QString rearorder="";
//        qDebug()<<"添加的条件有：";
        foreach(auto item,mutiple_condition)
        {
            rearorder+=text_map[item.first];
            rearorder+="=='"+item.second+"' and ";
//            qDebug()<<text_map[item.first]<<item.second;
        }
        rearorder=rearorder.left(rearorder.length()-4);
        QSqlQuery query;
//        qDebug()<<"多选语句"<<rearorder;
        query.exec(QString("select name,price,discount,inventory,producer from goods where %1;").arg(rearorder));
        while(query.next())
        {
            goods tmp={query.value(0).toString(),query.value(1).toFloat(),query.value(2).toFloat(),(unsigned)query.value(3).toInt(),query.value(4).toString()};
            record<<tmp;
        }

        show_data();
        mutiple_condition.clear();
     }
}

void MainSystem::show_data()//更新的数据呈现
{
    ui->tableWidget->clearContents();//去除原有表格中的数据
    ui->tableWidget->setRowCount(record.count());
    for(int i=0;i<record.length();i++)
    {
        int col=0;
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].inventory)));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(record[i].name));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].discount)));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].price)));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].discount*record[i].price)));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(record[i].producer)));
        int pieces=if_sold(record[i].name);
        if(pieces==0)//如果未卖出过
        {
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem("0"));
        ui->tableWidget->setItem(i,col++,new QTableWidgetItem("Nothing"));
        }
        else
        {
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(QString("%1").arg(pieces)));
            ui->tableWidget->setItem(i,col++,new QTableWidgetItem(get_sole_time(record[i].name)));
        }
    }
}

void MainSystem::on_checkBox_stateChanged(int arg1)//开启多选
{
    record.clear();
    if(arg1==0)//妹有勾选
    {
        ui->pushButton_12->hide();
        if_mutiple=false;
    }
    else//勾选了多选
    {
        if_mutiple=true;
       ui->pushButton_12->show();
    }
}

void MainSystem::on_pushButton_13_clicked()//返回
{
    ui->pushButton_13->hide();
    ui->pushButton_6->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();

    ui->comboBox->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
    ui->lineEdit->hide();
    ui->checkBox->hide();
    ui->checkBox->hide();
}

void MainSystem::on_pushButton_12_clicked()//这里是添加条件的函数
{
    QPair<QString,QString> tmp;
    if_mutiple=true;
    tmp.first=ui->comboBox->currentText();//获取当前的字段，然后转换为对应的额数据库字段
    tmp.second=ui->lineEdit->text();//获取条件限定的值
    ui->lineEdit->clear();//获取后清空输入框
    mutiple_condition.append(tmp);//有多个条件依次加入容器中

    QMessageBox *tishi=new QMessageBox();//提示框
    foreach(auto item,mutiple_condition)
    {
        tishi->setText(item.first+":"+item.second+"\n");
    }
    tishi->setWindowTitle("添加成功!");
    tishi->show();

}

void MainSystem::on_pushButton_clicked()
{
    QMessageBox *help=new QMessageBox();
    help->setText("鸽了！咕咕咕咕咕咕咕咕咕咕咕…………");
    help->setWindowTitle("咕咕咕");
    help->show();
}

void MainSystem::on_mass_reg_clicked()
{
;
}

void MainSystem::on_pushButton_6_clicked()
{
    sell *sell_ui=new sell();
    connect(sell_ui,SIGNAL(send_sell()),this,SLOT(update_current()));
    sell_ui->show();
}
int MainSystem::if_sold(QString name)
{
    QSqlQuery query;
    query.exec("select pieces from sold where name=='"+name+"'");
    query.next();
    return query.value(0).toInt();
}
QString MainSystem::get_sole_time(QString name)
{
    QSqlQuery query;
    query.exec("select DATETIME('NOW','LOCALTIME');");
    query.next();
    return query.value(0).toString();
}
