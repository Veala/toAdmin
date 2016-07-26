#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "rights.h"
#include "userdialog.h"
#include "lp.h"

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent, QSqlDatabase &db);
    ~Admin();

    QSqlTableModel *tmUsers;
    Rights *rights;
    //QSqlQueryModel *tusers;

public slots:
    void sorting(int,Qt::SortOrder);
    void addUser();
    void delUser();
    void accessRights();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
