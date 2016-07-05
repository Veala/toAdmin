#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0, QSqlDatabase *users);
    ~Admin();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
