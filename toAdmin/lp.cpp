#include "lp.h"

LP::LP(QObject *parent, QSqlDatabase &dtb, QString l, QString p, int uid, int rid) : QObject(parent)
{
    userId = uid;
    currentRihgtId = rid;
    newLogin = l;
    newPassword = p;
    db = &dtb;
    table = new QSqlQuery(*db);
}

//---------------------------------------idUser---idLP---Login---Password----------------------------------------------------
int LP::init(QString type)
{
    try {
        table.exec(QString("SELECT first.tabusers_idtabusers, first.TabLoginpassword_idtabloginpassword, second.login, second.password "
                           "FROM tabaccessrights first, tabloginpassword second "
                           "WHERE first.tabloginpassword_idtabloginpassword = second.idtabloginpassword;"));
        switch (type) {
        case "newUser();"   :   newUser();  break;
        case "changeLP();"  :   changeLP(); break;
        case "delUser();"   :   delUser();  break;
        case "delRight();"  :   delRight(); break;
        default             :   break;
        }
        return 1;
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
