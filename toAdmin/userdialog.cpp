#include "userdialog.h"
#include "ui_userdialog.h"

userDialog::userDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    this->setWindowIcon(QIcon(":/img/img.png"));

    connect(this, SIGNAL(accepted()), this, SLOT(setData()));
}

userDialog::~userDialog()
{
    delete ui;
}

void userDialog::setData()
{
    data.append(ui->lineEdit->text());     data.append(ui->lineEdit_2->text());
    data.append(ui->lineEdit_3->text());   data.append(ui->lineEdit_4->text());
    data.append(ui->lineEdit_5->text());   data.append(ui->lineEdit_6->text());
    data.append(ui->lineEdit_7->text());   flat = ui->spinBox->value();
}
