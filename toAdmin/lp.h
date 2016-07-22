#ifndef LP_H
#define LP_H

#include <QObject>
#include <QtSql>
#include <QTableView>
#include <QMessageBox>

class LP : public QObject
{
    Q_OBJECT
public:
    explicit LP(QObject *parent, QSqlDatabase &dtb, QString l, QString p, int uid);
    QString newLogin;
    QString newPassword;
    int userId;
    QSqlDatabase *db;
    QSqlQuery *table;

    int init(QString);
    void newUser();
    void changeLP();
    void delUser();
    void delRight();

signals:

public slots:

};

#endif // LP_H
