#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtSql>

enum typeError{
    BEGIN, ROLLBACKOK, ROLLBACKERR,

    PROGRAMMERROR, OTHER
};

class trException
{
public:
    explicit trException(typeError &tp, const QString &str);
    typeError type;
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
