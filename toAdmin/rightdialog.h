/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#ifndef RIGHTDIALOG_H
#define RIGHTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QPushButton>
#include <QMessageBox>
#include "lp.h"

namespace Ui {
class rightDialog;
}

class rightDialog : public QDialog, public Transaction
{
    Q_OBJECT

public:
    explicit rightDialog(QWidget *parent, QVector<QStringList> &strLists, int Key, QSqlDatabase &database);
    ~rightDialog();

    QStringList data;
    int uKey, lpID;
    QMessageBox messageBox;
    QRegExpValidator* Validator;

public slots:
    void clickOK(bool);
    void setData();

private:
    Ui::rightDialog *ui;
};

#endif // RIGHTDIALOG_H
