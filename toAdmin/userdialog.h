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

namespace Ui {
class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent = 0);
    ~userDialog();

    QStringList data;
    int flat;
    QMessageBox messageBox;
    QRegExpValidator* Validator;

public slots:
    void setData();

private:
    Ui::userDialog *ui;
};

#endif // USERDIALOG_H
