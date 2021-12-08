#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <QMainWindow>
#include<log_in.h>
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

private:
    Ui::MainSystem *ui;
};

#endif // MAINSYSTEM_H
