#include "log_in.h"
#include "ui_log_in.h"
#include"ctrl_admin.h"

QSqlDatabase database= QSqlDatabase::addDatabase("QSQLITE");
bool if_god_mode=false;
QStringList common;

log_in::log_in(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::log_in)
{
    ui->setupUi(this);
    database.setDatabaseName("qt.db");
    database.open();
    adduser();//创建窗口时，加载账户数据
}

log_in::~log_in()
{
    database.close();
    delete ui;
}

void log_in::on_pushButton_2_clicked() //退出按钮
{
    close();
}

void log_in::on_pushButton_clicked() //验证登录
{
    switch (validate_pwd(ui->lineEdit_2->text(),ui->comboBox->currentText())) {
    case 1:
    {
        //进入高级用户模式
        ctrl_admin *ctrladmin=new ctrl_admin();
        ctrladmin->show();    close();
        if_god_mode=false;
        break;
    }
    case 2:
    {
        //进入普通用户模式
        close();
        MainSystem *mainSystem=new MainSystem();
        mainSystem->show();    close();
        break;
    }
    case -1:
        break;
    }
}

int log_in::validate_pwd(QString pwd,QString admin)
{
    if(pwd=="")
    {
        showError("啥也没有","你在想啥呢？");
        return false;
    }
    if(if_god_mode==false)
    {
        QString each;

        if(common.contains(admin))
{
            if(pwd=="root")
            {
                return 2;
            }
            else
            {
                showError("口令错误","你再仔细想想？");
                return -1;
            }
}
        showError("户名错误","啥也不是");
        return -1;
    }
    else
    {
        if(ui->comboBox->currentText()=="super")
        {
            if(pwd=="god")
                return 1;
            else
                showError("口令错误","你再仔细想想？");
            return -1;
        }
        else
        {
            showError("户名错误","你不是高级用户");
            return -1;
        }
    }
}

void log_in::on_checkBox_stateChanged(int arg1)
{
    if(arg1==0)
    {
        if_god_mode=false;
        ui->label->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(29, 140, 216, 255), stop:1 rgba(255, 255, 255, 255));");
        ui->label_3->setText("用户名称\n\n登录口令");
        adduser();
    }
    else
    {
        //选中改变当前窗口样式
        if_god_mode=true;
        ui->label->setStyleSheet("background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(211, 26, 18, 255), stop:1 rgba(255, 255, 255, 255));");
        ui->label_3->setText("高级户名\n\n高级口令");
        ui->lineEdit_2->setText("");
        int allitems=ui->comboBox->count();
        for(int i=0;i<allitems;i++)
        {
           ui->comboBox->removeItem(0);
        }
    }
}

void log_in::showError(QString title,QString content)
{
    QMessageBox error;
    error.setWindowTitle(title);
    error.setText(content);
    error.setFixedSize(180,240);
    error.show();
    error.exec();
}

void log_in::adduser()
{
    QSqlQuery query;
    query.exec("select name from admin");//把账户更新到下拉框里,并且更新内存里的账户数据
    common.clear();
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
        common.append(query.value(0).toString());
    }
}
