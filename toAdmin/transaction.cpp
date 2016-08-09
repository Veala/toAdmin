#include "transaction.h"

Transaction::Transaction(QSqlDatabase &db)
{
    begin = new QSqlQuery(db);  begin->prepare(QString("BEGIN;"));
    commit = new QSqlQuery(db); commit->prepare(QString("COMMIT;"));
}

Transaction::~Transaction()
{
    delete begin;
    delete commit;
}

void Transaction::begin()
{
    if (!begin->exec()) throw QString("BEGIN");
}

void Transaction::commit()
{
    if (!commit->exec()) throw QString("COMMIT");
}

