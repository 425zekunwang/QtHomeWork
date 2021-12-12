#ifndef LOG_IN_H
#define LOG_IN_H

#include <QMainWindow>
#include<mainsystem.h>
#include<QSqlDatabase>
#include<QSqlQuery>
namespace Ui {
class log_in;
}

class User
{
public:
    QString name;
private:
    void query();
    void sell();
};

class God:public User
{
private:
    bool creatUser(QString);
    bool delUser(QString);

};
typedef struct goods
{
    QString name;
    float price;
    float discount;
    unsigned int inventory;//库存
}goods;
class log_in : public QMainWindow
{
    Q_OBJECT

public:
    explicit log_in(QWidget *parent = nullptr);
    void showError(QString,QString);
    void adduser();
    ~log_in();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    int validate_pwd(QString pwd,QString admin);
    void on_checkBox_stateChanged(int arg1);
signals:
    void sendPwd(QString);
private:
    Ui::log_in *ui;
};

#endif // LOG_IN_H
