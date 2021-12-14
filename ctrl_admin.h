#ifndef CTRL_ADMIN_H
#define CTRL_ADMIN_H

#include <QWidget>

namespace Ui {
class ctrl_admin;
}

class ctrl_admin : public QWidget
{
    Q_OBJECT

public:
    explicit ctrl_admin(QWidget *parent = nullptr);
    ~ctrl_admin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void receivedata(bool);
    void update_current();
private:
    Ui::ctrl_admin *ui;
};

#endif // CTRL_ADMIN_H
