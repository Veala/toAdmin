#include "rightdialog.h"
#include "ui_rightdialog.h"

rightDialog::rightDialog(QWidget *parent, QVector<QStringList> &strLists, int Key, const QSqlDatabase &database) :
    QDialog(parent),
    ui(new Ui::rightDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItems(strLists.at(0));
    ui->comboBox_2->addItems(strLists.at(1));
    ui->comboBox_3->addItems(strLists.at(2));
    connect(this, SIGNAL(accepted()), this, SLOT(setData()));
    connect(ui->pushButton_Ok,SIGNAL(clicked(bool)),this,SLOT(clickOK(bool)));
    connect(ui->pushButton_Close,SIGNAL(clicked(bool)),this,SLOT(reject()));
    db = &database;
    uKey = Key;
}

rightDialog::~rightDialog()
{
    delete ui;
}

bool rightDialog::checkLogin()
{
    QString login = ui->lineEdit->text();
    QSqlQuery loginQuery(*db);
    if (!loginQuery.exec(QString("SELECT idTabLoginPassword, login FROM tabloginpassword WHERE login = \"%1\";").arg(login))) {
        QMessageBox::warning(this, tr("Добавление права"), tr("Ошибка при добавлении: ") + loginQuery.lastError().text());
        return false;
    }
    if (loginQuery.size() == 0) {
        return true;
    }
    loginQuery.next();
    int idLP = loginQuery.value(0).toInt();

//    if (!loginQuery.exec(QString("SELECT idTabLoginPassword, login FROM tabloginpassword WHERE login = \"%1\";").arg(login))) {
//        QMessageBox::warning(this, tr("Добавление права"), tr("Ошибка при добавлении: ") + loginQuery.lastError().text());
//        return false;
//    }
//    if () {

//    }
}

void rightDialog::clickOK(bool b)
{
    QString login = ui->lineEdit->text();
    QSqlQuery loginQuery(*db);
    if (!loginQuery.exec(QString("SELECT idTabLoginPassword, login FROM tabloginpassword WHERE login = \"%1\";").arg(login))) {
        QMessageBox::warning(this, tr("Добавление права"), tr("Ошибка при добавлении: ") + loginQuery.lastError().text());
        return;
    }
    if (loginQuery.size() == 0) {

    }

    accept();

}

void rightDialog::setData()
{
    data.append(ui->lineEdit->text());                              data.append(ui->lineEdit_2->text());
    data.append(QString::number(ui->comboBox->currentIndex()));     data.append(QString::number(ui->comboBox_2->currentIndex()));
    data.append(QString::number(ui->comboBox_3->currentIndex()));
}
