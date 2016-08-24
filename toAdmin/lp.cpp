/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "lp.h"

lpException::lpException(const QString &str)
{
    data = str;
}

LP::LP(QObject *parent, QSqlDatabase &database, QString l, QString p, int uid) : QObject(parent), Transaction(database)
{
    userId = uid;   newLogin = l;   newPassword = p;
    table = new QSqlQuery(*db);
    mType["newRight();"] = 1;   mType["changeLP_1();"] = 2; mType["changeLP_2();"] = 3;
    simpleLogins << "";     //?
    simplePasswords << "";  //?
}

LP::~LP()
{
    delete table;
}

//---------------------------------------idUser---idLP---Login---Password----------------------------------------------------
void LP::init(QString type)
{
    try {
        setup();
        switch (mType[type]) {
        case 1  :   newRight();    break;
        case 2  :   changeLP_1();  break;
        case 3  :   changeLP_2();  break;
        default :   break;
        }
        throw lpException("Ok");
    }
    catch (const lpException& err) {
        error = err.data;
    }
}

void LP::setup()
{
    checkTemplate();
    if(!table->exec(QString("SELECT first.tabusers_idtabusers, first.TabLoginpassword_idtabloginpassword, second.login, second.password "
                            "FROM tabaccessrights first, tabloginpassword second "
                            "WHERE first.tabloginpassword_idtabloginpassword = second.idtabloginpassword "
                            "AND second.login = \"%1\";").arg(newLogin))) rollback(QString("Select lp 0: " + table->lastError().text()));
}

void LP::newRight()
{
    if (table->size() == 0) {   createNewLP();  return; }
    table->next();
    if (table->value(0).toInt() != userId) throw lpException(tr("данный логин занят другим пользователем"));
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
    if(!qPrevLpID.exec(QString("SELECT TabLoginPassword_idTabLoginPassword FROM tabaccessrights "
                               "WHERE TabLoginPassword_idTabLoginPassword = %1;").arg(QString::number(prevLpID))))
        rollback(QString("Select lp 1: " + qPrevLpID.lastError().text()));
    if (qPrevLpID.size() >= 1) return;
    if(!qPrevLpID.exec(QString("DELETE FROM tabloginpassword WHERE idTabLoginPassword = %1;").arg(QString::number(prevLpID))))
        rollback(QString("DELETE FROM lp 0: " + qPrevLpID.lastError().text()));
}

void LP::checkTemplate()
{
    if (newLogin.length() < 4) throw lpException(tr("логин должен быть не менее 4 символов"));
    if (newPassword.length() < 6) throw lpException(tr("пароль должен быть не менее 6 символов"));
    foreach (QString sl, simpleLogins) {
        if (sl == newLogin) throw lpException(tr("слишком простой логин"));
    }
    foreach (QString sp, simplePasswords) {
        if (sp == newPassword) throw lpException(tr("слишком простой пароль"));
    }
}

void LP::createNewLP()
{
    QSqlQuery newLP(*db);
    if(!newLP.exec(QString("INSERT INTO tabloginpassword (login, password) VALUES ('%1', '%2');").arg(newLogin, newPassword)))
        rollback(QString("INSERT INTO lp 0: " + newLP.lastError().text()));
    lpID = newLP.lastInsertId().toInt();
//    qDebug() << "last id: " + QString::number(newLP.lastInsertId().toInt());
}
