#include "lp.h"

LP::LP(QObject *parent, QSqlDatabase &dtb, QString l, QString p, int uid) : QObject(parent)
{
    userId = uid;
    newLogin = l;
    newPassword = p;
    db = &dtb;
    table = new QSqlQuery(*db);
}

int LP::init(QString type)
{
    try {
        table.exec(QString(""
                                                 ""));
        switch (type) {
        case "newUser();"   :   newUser();  break;
        case "changeLP();"  :   changeLP(); break;
        case "delUser();"   :   delUser();  break;
        case "delRight();"  :   delRight(); break;
        default             :   break;
        }
    } catch (...) {
        QMessageBox::warning(0,tr("Ошибка"),tr("Ошибка: операция выполнена неуспешно, повторите попытку позже"));
        return 0;
    }
}

void LP::newUser()
{

}

void LP::changeLP()
{

}

void LP::delUser()
{

}

void LP::delRight()
{

}
