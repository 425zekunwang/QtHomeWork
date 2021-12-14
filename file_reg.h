#ifndef FILE_REG_H
#define FILE_REG_H

#include <QWidget>

namespace Ui {
class file_reg;
}

class file_reg : public QWidget
{
    Q_OBJECT

public:
    explicit file_reg(QWidget *parent = nullptr);
    ~file_reg();

private:
    Ui::file_reg *ui;
};

#endif // FILE_REG_H
