#ifndef SELL_H
#define SELL_H

#include <QWidget>

namespace Ui {
class sell;
}

class sell : public QWidget
{
    Q_OBJECT

public:
    explicit sell(QWidget *parent = nullptr);
    ~sell();

private slots:

    void on_pushButton_clicked();
signals:
    void send_sell();
private:
    Ui::sell *ui;
};

#endif // SELL_H
