#ifndef DATAQUERY_H
#define DATAQUERY_H

#include <QMainWindow>

namespace Ui {
class dataQuery;
}

class dataQuery : public QMainWindow
{
    Q_OBJECT

public:
    explicit dataQuery(QWidget *parent = nullptr);
    ~dataQuery();

private:
    Ui::dataQuery *ui;
};

#endif // DATAQUERY_H
