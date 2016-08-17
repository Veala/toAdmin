#include "transaction.h"

trException::trException(const QString &tp, const QString &str)
{
    type = tp;  data = str;
}

Transaction::Transaction(QSqlDatabase &database)
{
    db = &database;
    //tx_isolation | REPEATABLE-READ
    //
//    qBegin = new QSqlQuery(db);      qBegin->prepare(QString("BEGIN;"));
//    qCommit = new QSqlQuery(db);     qCommit->prepare(QString("COMMIT;"));
//    qRollback = new QSqlQuery(db);   qRollback->prepare(QString("ROLLBACK;"));
}

Transaction::~Transaction()
{
//    delete qBegin;
//    delete qCommit;
//    delete qRollback;
}

void Transaction::begin()
{
    if (!db->transaction()) throw QString("BEGIN: " + db->lastError().text());
}

void Transaction::commit()
{
    if (!db->commit()) throw QString("COMMIT: " + db->lastError().text());
}

void Transaction::rollback(QString error)
{
    if (!db->rollback()) throw trException(error, "ROLLBACK: " + db->lastError().text());
}
