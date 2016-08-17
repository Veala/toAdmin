#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtSql>

class trException
{
public:
    explicit trException(const QString &tp, const QString &str);
    QString type;
    QString data;
};

class Transaction
{
public:
    Transaction(QSqlDatabase &database);
    ~Transaction();

    QSqlDatabase *db;
    //QSqlQuery *qBegin, *qCommit, *qRollback;
    void begin();
    void commit();
    void rollback(QString);
};

#endif // TRANSACTION_H
