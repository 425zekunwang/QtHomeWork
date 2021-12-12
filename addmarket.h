#ifndef ADDMARKET_H
#define ADDMARKET_H

#include <QWidget>

namespace Ui {
class addMarket;
}

class addMarket : public QWidget
{
    Q_OBJECT

public:
    explicit addMarket(QWidget *parent = nullptr);
    ~addMarket();

private slots:
    void on_pushButton_clicked();
signals:
    void sendData(QString);
private:
    Ui::addMarket *ui;
};

#endif // ADDMARKET_H
