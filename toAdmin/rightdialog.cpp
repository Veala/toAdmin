/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "rightdialog.h"
#include "ui_rightdialog.h"

rightDialog::rightDialog(QWidget *parent, QVector<QStringList> &strLists, int Key, QSqlDatabase &database) :
    QDialog(parent), Transaction(database),
    ui(new Ui::rightDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));
    QRegExp rx("[0-9A-Za-z]+");
    Validator = new QRegExpValidator(rx,this);
    ui->lineEdit->setValidator(Validator);
    ui->lineEdit_2->setValidator(Validator);
    ui->comboBox->addItems(strLists.at(0));
    ui->comboBox_2->addItems(strLists.at(1));
    ui->comboBox_3->addItems(strLists.at(2));
    connect(this, SIGNAL(accepted()), this, SLOT(setData()));
    connect(ui->pushButton_Ok,SIGNAL(clicked(bool)),this,SLOT(clickOK(bool)));
    connect(ui->pushButton_Close,SIGNAL(clicked(bool)),this,SLOT(reject()));
    uKey = Key;
}

rightDialog::~rightDialog()
{
    delete ui;
}

void rightDialog::clickOK(bool)
{
    try {
        QString login    = ui->lineEdit->text();
        QString password = ui->lineEdit_2->text();
        LP lp(0, *db, login, password, uKey);
        lp.init("newRight();");
        if (lp.error == "Ok") {
            lpID = lp.lpID;
            accept();
        } else {
            messageBox.warning(this, tr("Добавление права пользователя"), tr("Ошибка: ") + lp.error);
        }
    }
    catch (const trException& error) {
        trError.type = error.type;
        trError.data = error.data;
        reject();
    }
    catch (...) {
        messageBox.warning(this, tr("Ошибка добавления"), tr("Операция выполнена неуспешно, повторите попытку позже"));
        reject();
    }
}

void rightDialog::setData()
{
    data.append(ui->lineEdit->text());                              data.append(ui->lineEdit_2->text());
    data.append(QString::number(ui->comboBox->currentIndex()));     data.append(QString::number(ui->comboBox_2->currentIndex()));
    data.append(QString::number(ui->comboBox_3->currentIndex()));
}
