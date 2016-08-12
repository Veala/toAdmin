#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtSql>

class rollBackException
{
public:
    explicit rollBackException(const QString &str);
    QString data;
};

class Transaction
{
public:
    Transaction(const QSqlDatabase &db);
    ~Transaction();
    QSqlQuery *qBegin, *qCommit, *qRollback;
    void begin();
    void commit();
    void rollback();
};

#endif // TRANSACTION_H
