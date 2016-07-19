#ifndef RIGHTDIALOG_H
#define RIGHTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class rightDialog;
}

class rightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rightDialog(QWidget *parent, QVector<QStringList> &strLists, int Key, const QSqlDatabase &database);
    ~rightDialog();
    QStringList data;
    const QSqlDatabase *db;
    int uKey, lpKey;
    bool checkLogin();

public slots:
    void clickOK(bool);
    void setData();

private:
    Ui::rightDialog *ui;
};

#endif // RIGHTDIALOG_H
