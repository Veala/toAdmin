#include "lp.h"

LP::LP(QObject *parent, const QSqlDatabase &dtb, QString l, QString p, int uid) : QObject(parent)
{
    userId = uid;
    newLogin = l;
    newPassword = p;
    db = &dtb;
    table = new QSqlQuery(*db);
}

LP::~LP()
{
    qDebug() << "delete table";
    delete table;
}

//---------------------------------------idUser---idLP---Login---Password----------------------------------------------------
void LP::init(QString type)
{
    int intType;
    if (type == "newRight();") intType = 1;
    else if (type == "changeLP_1();") intType = 2;
    else if (type == "changeLP_2();") intType = 3;
    try {
        switch (intType) {
        case 1  :   setup();  newRight();    break;
        case 2  :   setup();  changeLP_1();  break;
        case 3  :   setup();  changeLP_2();  break;
        default :   break;
        }
        throw QString("Ok");
    }
    catch (const QString& err) {
        error = err;
    }
    catch (...) {
        error = "Ошибка: операция выполнена неуспешно, повторите попытку позже";
    }
}

void LP::setup()
{
    table->exec(QString("SELECT first.tabusers_idtabusers, first.TabLoginpassword_idtabloginpassword, second.login, second.password "
                       "FROM tabaccessrights first, tabloginpassword second "
                       "WHERE first.tabloginpassword_idtabloginpassword = second.idtabloginpassword "
                       "AND second.login = \"%1\";").arg(newLogin));
    checkTemplate();
}

void LP::newRight()
{
    if (table->size() == 0) {   createNewLP();  return; }
    table->next();
    if (table->value(0).toInt() != userId) throw QString(tr("Данный логин занят другим пользователем"));
    table->previous();  lpID = -1;
    while (table->next())   if (table->value(3).toString() == newPassword) { lpID = table->value(1).toInt(); break; }
    if (lpID != -1) return;
    createNewLP();
}

void LP::changeLP_1()
{
    lpID = -1;
    while (table->next())   if (table->value(3).toString() == newPassword) { lpID = table->value(1).toInt(); break; }
    if (lpID == -1) createNewLP();
    //delPrevLP();
}

void LP::changeLP_2()
{
    newRight();
    //delPrevLP();
}

void LP::delPrevLP()
{
    QSqlQuery qPrevLpID(*db);
    qPrevLpID.exec(QString("SELECT TabLoginPassword_idTabLoginPassword FROM tabaccessrights "
                           "WHERE TabLoginPassword_idTabLoginPassword = %1;").arg(QString::number(prevLpID)));
    if (qPrevLpID.size() >= 1) return;
    qPrevLpID.exec(QString("DELETE FROM tabloginpassword WHERE idTabLoginPassword = %1;").arg(QString::number(prevLpID)));
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
//    qDebug() << "last id: " + QString::number(newLP.lastInsertId().toInt());
}
