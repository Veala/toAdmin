/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

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

class Admin : public QMainWindow, public Transaction
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent, QSqlDatabase &database);
    ~Admin();

    QSqlTableModel *tmUsers;
    Rights *rights;
    QMessageBox messageBox;
signals:
    void sError(QString);
public slots:
    void sorting(int,Qt::SortOrder);
    void addUser();
    void delUser();
    void accessRights();
    void error(const trException, QString);

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
