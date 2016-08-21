#include "transaction.h"

Transaction::Transaction(QSqlDatabase &database)
{
    db = &database;
    //tx_isolation | REPEATABLE-READ
}

void Transaction::begin()
{
    if (!db->transaction()) throw trException(BEGIN_ERR, "BEGIN error: " + db->lastError().text());
}

void Transaction::commit()
{
    if (!db->commit())  rollback(QString("COMMIT error: " + db->lastError().text()));
}

void Transaction::rollback(QString error)
{
    if (!db->rollback())                        throw trException(ROLLBACK_CRITICAL_ERR,  error + "\n" + "ROLLBACK error: " + db->lastError().text());
    else if (error != "standard situation")     throw trException(ROLLBACK_OK_ERR,   error + "\n" + "ROLLBACK: OK");
}


Transaction::trException::trException()
{
    type = NO_ERR;  data = "";
}

Transaction::trException::trException(typeError tp, QString str)
{
    type = tp;  data = str;
}
