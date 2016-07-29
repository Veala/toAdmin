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
    explicit LP(QObject *parent, const QSqlDatabase &dtb, QString l, QString p, int uid);
    ~LP();
    QString newLogin;
    QString newPassword;
    int userId;
    int lpID;
    int prevLpID;
    const QSqlDatabase *db;
    QSqlQuery *table;

    void init(QString);
    void setup();
    void newRight();
    void changeLP_1();      //login тот же, password другой
    void changeLP_2();      //login другой, password другой
    void delPrevLP();

    void checkTemplate();
    void createNewLP();

    QString error;
signals:

public slots:

};

#endif // LP_H
