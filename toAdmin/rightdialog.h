#ifndef RIGHTDIALOG_H
#define RIGHTDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QPushButton>

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
    QSqlDatabase db;
    int uKey;

public slots:
    void boxClicked(QAbstractButton*);
    void setData();

private:
    Ui::rightDialog *ui;
};

#endif // RIGHTDIALOG_H