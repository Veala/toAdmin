#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtSql>

class Transaction
{
public:
    Transaction(QSqlDatabase &database);
    enum typeError{
        NO_ERR,
        BEGIN_ERR, ROLLBACK_OK_ERR, ROLLBACK_CRITICAL_ERR,
        OTHER_ERR
    };
    class trException
    {
    public:
        explicit trException();
        explicit trException(typeError tp, QString str);
        typeError type;
        QString data;
        //bool operator
    } trError;
    QSqlDatabase *db;
    void begin();
    void commit();
    void rollback(QString);
};

#endif // TRANSACTION_H
