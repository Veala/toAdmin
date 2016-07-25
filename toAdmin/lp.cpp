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
void LP::init(QString type)
{
    try {
        table.exec(QString("SELECT first.tabusers_idtabusers, first.TabLoginpassword_idtabloginpassword, second.login, second.password "
                           "FROM tabaccessrights first, tabloginpassword second "
                           "WHERE first.tabloginpassword_idtabloginpassword = second.idtabloginpassword "
                           "AND second.login = \"%1\";").arg(newLogin));
        rec = table->record();
        checkTemplate();
        switch (type) {
        case "newUser();"     :   newUser();    break;
        case "changeLP_1();"  :   changeLP_1(); break;
        case "changeLP_2();"  :   changeLP_2(); break;
        case "delUser();"     :   delUser();    break;
        case "delRight();"    :   delRight();   break;
        default               :   break;
        }
        throw "Ok";
    }
    catch (const QString& err) {
        error = err;
    }
    catch (...) {
        error = "Ошибка: операция выполнена неуспешно, повторите попытку позже";
    }
}

void LP::newUser()
{
    if (table->size() == 0) {   createNewLP();  return; }
    table->next();
    if (rec.value(0).toInt() != userId) throw QString("Данный логин занят другим пользователем");
    table->previous();  lpID = -1;
    while (table->next())   if (rec.value(3).toString() == newPassword) { lpID = rec.value(1).toInt(); break; }
    if (lpID != -1) return;
    createNewLP();
}

void LP::changeLP_1()
{
    lpID = -1;
    while (table->next())   if (rec.value(3).toString() == newPassword) { lpID = rec.value(1).toInt(); break; }
    if (lpID == -1) createNewLP();
    delPrevLP();
}

void LP::changeLP_2()
{
    newUser();
    delPrevLP();
}

void LP::delPrevLP()
{
    QSqlQuery qPrevLpID(*db);
    qPrevLpID.exec(QString("SELECT TabLoginPassword_idTabLoginPassword FROM tabaccessrights "
                           "WHERE TabLoginPassword_idTabLoginPassword = %1;").arg(QString::number(prevLpID)));
    if (qPrevLpID.size() > 1) return;
    qPrevLpID.exec(QString("DELETE FROM tabloginpassword WHERE idTabLoginPassword = %1;").arg(QString::number(prevLpID)));
}

void LP::delUser()
{

}

void LP::delRight()
{

}

void LP::checkTemplate()
{
    int i=1;
    if (i=1) return;
    else if (i=2)  throw QString("Слишком простой логин");
    else if (i=3)  throw QString("Слишком простой пароль");
}

void LP::createNewLP()
{
    QSqlQuery newLP(*db);
    newLP.exec(QString("INSERT INTO tabloginpassword (login, password) VALUES ('%1', '%2');").arg(newLogin, newPassword));
    lpID = newLP.lastInsertId().toInt();
    qDebug() << "last id: " + QString::number(newLP.lastInsertId().toInt());
}
