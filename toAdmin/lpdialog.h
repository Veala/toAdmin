/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#ifndef LPDIALOG_H
#define LPDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include "transaction.h"

namespace Ui {
class lpDialog;
}

class lpDialog : public QDialog, public Transaction
{
    Q_OBJECT

public:
    explicit lpDialog(QWidget *parent, QString curL, QString curP, QSqlDatabase &database);
    ~lpDialog();

    int lpID;
    QString currentL, currentP;
    QMessageBox messageBox;
    QRegExpValidator* Validator;

public slots:
    void clickOK(bool);

private:
    Ui::lpDialog *ui;
};

#endif // LPDIALOG_H
