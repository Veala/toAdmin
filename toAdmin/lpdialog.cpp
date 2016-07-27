#include "lpdialog.h"
#include "ui_lpdialog.h"

lpDialog::lpDialog(QWidget *parent, QString curL, QString curP, const QSqlDatabase &database) :
    QDialog(parent),
    ui(new Ui::lpDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_Ok,SIGNAL(clicked(bool)),this,SLOT(clickOK(bool)));
    connect(ui->pushButton_Close,SIGNAL(clicked(bool)),this,SLOT(reject()));
    db = &database;
    currentL = curL;
    currentP = curP;
    ui->lineEdit->setText(currentL);
    ui->lineEdit_2->setText(currentP);
}

lpDialog::~lpDialog()
{
    delete ui;
}

void lpDialog::clickOK(bool b)
{
    QString login    = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    LP lp(0, *db, login, password, uID);
    lp.prevLpID = lpID;
    if ((currentL == login) && (currentP == password)) {
        accept(); return;
    } else if ((currentL == login) && (currentP != password)) {
        lp.init("changeLP_1();");
    } else if (currentL != login) {
        lp.init("changeLP_2();");
    }
    if (lp.error == "Ok") {
        QSqlQuery update(*db);
        update.exec(QString("UPDATE tabaccessrights SET TabLoginPassword_idTabLoginPassword = %1 "
                            "WHERE idtabaccessrights = %2;").arg(QString::number(lp.lpID), QString::number(rID)));
        lp.delPrevLP();
        accept();
    } else {
        QMessageBox::warning(this, tr("Смена логина и пароля"), tr("Ошибка: %1").arg(lp.error));
    }
}
