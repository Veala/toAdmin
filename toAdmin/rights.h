#ifndef RIGHTS_H
#define RIGHTS_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>
#include <QMessageBox>
#include "rightdialog.h"
#include "lp.h"
#include "lpdialog.h"

namespace Ui {
class Rights;
}

class Rights : public QMainWindow, public Transaction
{
    Q_OBJECT

public:
    explicit Rights(QWidget *parent, QSqlDatabase &db);
    ~Rights();

    QSqlRelationalTableModel *tmRights;
    int uKey;
    QMessageBox messageBox;

public slots:
    void init(int uKey, QString uNmae);
    void sorting(int,Qt::SortOrder);
    void addRights();
    void logPas();
    void delRights();

private:
    Ui::Rights *ui;
};

#endif // RIGHTS_H
