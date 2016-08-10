#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtSql>

class Transaction
{
public:
    Transaction(QSqlDatabase &db);
    ~Transaction();
    void begin();
    void commit();
    void rollback();
    QSqlQuery *begin, *commit, *rollback;
};

#endif // TRANSACTION_H
