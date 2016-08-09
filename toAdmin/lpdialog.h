#ifndef LPDIALOG_H
#define LPDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QPushButton>
#include <QMessageBox>
#include "lp.h"

namespace Ui {
class lpDialog;
}

class lpDialog : public QDialog, public Transaction
{
    Q_OBJECT

public:
    explicit lpDialog(QWidget *parent, QString curL, QString curP, const QSqlDatabase &database);
    ~lpDialog();

    const QSqlDatabase *db;
    int uID, lpID, rID;
    QString currentL, currentP;
    QMessageBox messageBox;

public slots:
    void clickOK(bool);

private:
    Ui::lpDialog *ui;
};

#endif // LPDIALOG_H
