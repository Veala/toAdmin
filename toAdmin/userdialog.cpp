/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "userdialog.h"
#include "ui_userdialog.h"

userDialog::userDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));
    QRegExp rx("[0-9A-Za-zА-Яа-я-]+");
    Validator = new QRegExpValidator(rx,this);
    ui->lineEdit->setValidator(Validator);
    ui->lineEdit_2->setValidator(Validator);
    ui->lineEdit_3->setValidator(Validator);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setData()));
}

userDialog::~userDialog()
{
    delete ui;
}

void userDialog::setData()
{
    if (ui->lineEdit->text().length() < 1)      { messageBox.warning(this,tr("Синтаксическия ошибка"),tr("Фамилия должна быть не менее 1 символа"));    return; }
    if (ui->lineEdit_2->text().length() < 1)    { messageBox.warning(this,tr("Синтаксическия ошибка"),tr("Имя должно быть не менее 1 символа"));        return; }
    if (ui->lineEdit_3->text().length() < 1)    { messageBox.warning(this,tr("Синтаксическия ошибка"),tr("Отчество должно быть не менее 1 символа"));   return; }

    data.append(ui->lineEdit->text());     data.append(ui->lineEdit_2->text());
    data.append(ui->lineEdit_3->text());   data.append(ui->lineEdit_4->text());
    data.append(ui->lineEdit_5->text());   data.append(ui->lineEdit_6->text());
    data.append(ui->lineEdit_7->text());   flat = ui->spinBox->value();

    accept();
}
