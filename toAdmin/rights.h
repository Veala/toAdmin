/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#ifndef RIGHTS_H
#define RIGHTS_H

#include <QMainWindow>
#include <QTableView>
#include <QMessageBox>
#include "rightdialog.h"
#include "transaction.h"

namespace Ui {
class Rights;
}

class Rights : public QMainWindow, public Transaction
{
    Q_OBJECT

public:
    explicit Rights(QWidget *parent, QSqlDatabase &database);
    ~Rights();

    QSqlRelationalTableModel *tmRights;
    int uKey;
    QMessageBox messageBox;

signals:
    void sError(const trException, QString);
public slots:
    void init(int uKey, QString uNmae);
    void sorting(int,Qt::SortOrder);
    void addRights();
    void delRights();
    void error(const trException, QString);

private:
    Ui::Rights *ui;
};

#endif // RIGHTS_H
