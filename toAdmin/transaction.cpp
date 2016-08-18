#include "transaction.h"

trException::trException(typeError &tp, QString &str)
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
    if (!db->transaction()) throw trException(BEGIN, "BEGIN error: " + db->lastError().text());
}

void Transaction::commit()
{
    if (!db->commit())  rollback(QString("COMMIT error: " + db->lastError().text()));
}

void Transaction::rollback(QString error)
{
    if (!db->rollback())                        throw trException(ROLLBACKERR,  error + "\n" + "ROLLBACK error: " + db->lastError().text());
    else if (error != "standard situation")     throw trException(ROLLBACKOK,   error + "\n" + "ROLLBACK: OK");
}
