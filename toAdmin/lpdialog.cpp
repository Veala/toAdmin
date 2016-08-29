/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "lpdialog.h"
#include "ui_lpdialog.h"

lpDialog::lpDialog(QWidget *parent, QString curL, QString curP, QSqlDatabase &database) :
    QDialog(parent), Transaction(database),
    ui(new Ui::lpDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));
    QRegExp rx("[0-9A-Za-z]+");
    Validator = new QRegExpValidator(rx,this);
    ui->lineEdit->setValidator(Validator);
    ui->lineEdit_2->setValidator(Validator);
    ui->lineEdit_3->setValidator(Validator);
    connect(ui->pushButton_Ok,SIGNAL(clicked(bool)),this,SLOT(clickOK(bool)));
    connect(ui->pushButton_Close,SIGNAL(clicked(bool)),this,SLOT(reject()));
    currentL = curL; currentP = curP;
    ui->lineEdit->setText(currentL); ui->lineEdit_2->setText(currentP); ui->lineEdit_3->setText(currentP);
}

lpDialog::~lpDialog()
{
    delete ui;
}

void lpDialog::clickOK(bool)
{
    try {
        QString login    = ui->lineEdit->text();    QString password = ui->lineEdit_2->text();
        if (login.length() < 4)         { messageBox.warning(this,tr("Синтаксическия ошибка"),tr("Логин должен быть не менее 4 символов"));     return; }
        if (password.length() < 6)      { messageBox.warning(this,tr("Синтаксическия ошибка"),tr("Пароль должен быть не менее 6 символов"));    return; }
        if (password != ui->lineEdit_3->text())    { messageBox.warning(this,tr("Ошибка паролей"),tr("Ошибка в подтверждении пароля, введите пароли заново"));     return; }
        QSqlQuery update(*db);
        if ((currentL == login) && (currentP == password)) {
            accept();
        } else if ((currentL == login) && (currentP != password)) {
            if(!update.exec(QString("UPDATE tabloginpassword SET password = \"%1\" "
                                    "WHERE idTabLoginPassword = %2;").arg(password, QString::number(lpID))))
                rollback(QString("Update 1: " + update.lastError().text()));
            accept();
        } else if (currentL != login) {
            if(!update.exec(QString("SELECT * FROM tabloginpassword WHERE login = \"%1\";").arg(login)))
                rollback(QString("SELECT lpDialog: " + update.lastError().text()));
            if (update.size() >= 1) { messageBox.warning(this, tr("Ошибка добавления пользователя"), tr("Данный логин занят другим пользователем")); return; }
            if(!update.exec(QString("UPDATE tabloginpassword SET login = \"%1\", password = \"%2\" "
                                    "WHERE idTabLoginPassword = %3;").arg(login, password, QString::number(lpID))))
                rollback(QString("Update 2: " + update.lastError().text()));
            accept();
        }
    }
    catch (const trException& error) {
        trError.type = error.type;
        trError.data = error.data;
        reject();
    }
    catch (...) {
        messageBox.warning(this, tr("Ошибка изменения \"логин-пароль\""), tr("Операция выполнена неуспешно, повторите попытку позже"));
        reject();
    }
}
