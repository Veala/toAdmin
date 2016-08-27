/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QValidator>
#include <QPushButton>
#include "transaction.h"

namespace Ui {
class userDialog;
}

class userDialog : public QDialog, public Transaction
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent, QSqlDatabase &database);
    ~userDialog();

    QStringList data;
    int flat;
    QMessageBox messageBox;
    QRegExpValidator* uValidator, *lpValidator;

public slots:
    void setData();

private:
    Ui::userDialog *ui;
};

#endif // USERDIALOG_H
