#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <QMainWindow>
#include<log_in.h>
#include"QMessageBox"
namespace Ui {
class MainSystem;
}

class MainSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSystem(QWidget *parent = nullptr);
    ~MainSystem();

private slots:
    void on_pushButton_8_clicked();
    void on_pushButton_2_clicked();
    int if_sold(QString);
    QString get_sole_time(QString);
    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void show_data();
    void update_current();
    void update_query(QString,QString);
    void on_pushButton_11_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_clicked();

    void on_mass_reg_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainSystem *ui;
};

#endif // MAINSYSTEM_H
