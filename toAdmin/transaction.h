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
    QSqlQuery *begin, *commit;
};

#endif // TRANSACTION_H
