/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "rightdialog.h"
#include "ui_rightdialog.h"

rightDialog::rightDialog(QWidget *parent, QVector<QStringList> &strLists) :
    QDialog(parent),
    ui(new Ui::rightDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    this->setWindowIcon(QIcon(":/img/img.png"));
    ui->comboBox->addItems(strLists.at(0));
    ui->comboBox_2->addItems(strLists.at(1));
    ui->comboBox_3->addItems(strLists.at(2));
    connect(ui->pushButton_Ok,SIGNAL(clicked(bool)),this,SLOT(setData(bool)));
    connect(ui->pushButton_Close,SIGNAL(clicked(bool)),this,SLOT(reject()));
}

rightDialog::~rightDialog()
{
    delete ui;
}

void rightDialog::setData(bool)
{
    data.append(QString::number(ui->comboBox->currentIndex()));
    data.append(QString::number(ui->comboBox_2->currentIndex()));
    data.append(QString::number(ui->comboBox_3->currentIndex()));
    accept();
}
