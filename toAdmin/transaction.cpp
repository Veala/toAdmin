#include "transaction.h"

Transaction::Transaction(QSqlDatabase &db)
{
    begin = new QSqlQuery(db);      begin->prepare(QString("BEGIN;"));
    commit = new QSqlQuery(db);     commit->prepare(QString("COMMIT;"));
    rollback = new QSqlQuery(db);   rollback->prepare(QString("ROLLBACK;"));
}

Transaction::~Transaction()
{
    delete begin;
    delete commit;
    delete rollback;
}

void Transaction::begin()
{
    if (!begin->exec()) throw QString("BEGIN");
}

void Transaction::commit()
{
    if (!commit->exec()) throw QString("COMMIT");
}

void Transaction::rollback()
{
    if (!rollback->exec()) throw QString("ROLLBACK");
}

