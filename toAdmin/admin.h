#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);//, QSqlDatabase users = QSqlDatabase::addDatabase("QMYSQL"));
    ~Admin();

    QSqlDatabase users;
    QSqlTableModel *tusers;
    //QSqlQueryModel *tusers;

public slots:
    void sorting(int,Qt::SortOrder);
    void addUser();
    void delUser();
    void accessRights();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
