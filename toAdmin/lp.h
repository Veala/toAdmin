#ifndef LP_H
#define LP_H

#include <QObject>
#include <QtSql>
#include <QTableView>
#include <QMessageBox>
#include "transaction.h"

class lpException {

public:
    explicit lpException(const QString &str);
    QString data;
};

class LP : public QObject
{
    Q_OBJECT
public:
    explicit LP(QObject *parent, const QSqlDatabase &dtb, QString l, QString p, int uid);
    ~LP();

    QString newLogin, newPassword;
    int userId, lpID, prevLpID;
    const QSqlDatabase *db;
    QSqlQuery *table;
    QMap<QString, int> mType;

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
