#include "transaction.h"

rollBackException::rollBackException(const QString &str)
{
    data = str;
}

Transaction::Transaction(const QSqlDatabase &db)
{
    qBegin = new QSqlQuery(db);      qBegin->prepare(QString("BEGIN;"));
    qCommit = new QSqlQuery(db);     qCommit->prepare(QString("COMMIT;"));
    qRollback = new QSqlQuery(db);   qRollback->prepare(QString("ROLLBACK;"));
}

Transaction::~Transaction()
{
    delete qBegin;
    delete qCommit;
    delete qRollback;
}

void Transaction::begin()
{
    if (!qBegin->exec()) throw QString("BEGIN: " + qBegin->lastError().text());
}

void Transaction::commit()
{
    if (!qCommit->exec()) throw QString("COMMIT: " + qCommit->lastError().text());
}

void Transaction::rollback()
{
    if (!qRollback->exec()) throw rollBackException("ROLLBACK: " + qRollback->lastError().text());
}
