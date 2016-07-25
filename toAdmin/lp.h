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
    explicit LP(QObject *parent, QSqlDatabase &dtb, QString l, QString p, int uid, int rid);
    QString newLogin;
    QString newPassword;
    int userId;
    int lpID;
    int prevLpID;
    int currentRihgtId;     //если идет добавление то -1, если удаление то реальный id
    QSqlDatabase *db;
    QSqlQuery *table;
    QSqlRecord rec;

    void init(QString);
    void newUser();
    void changeLP_1();      //login тот же, password другой
    void changeLP_2();      //login другой, password другой
    void delPrevLP();
    void delUser();
    void delRight();

    void checkTemplate();
    void createNewLP();

    QString error;
signals:

public slots:

};

#endif // LP_H
