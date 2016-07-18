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
    //connect(this, SIGNAL(accepted()), this, SLOT(setData()));
    connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(boxClicked(QAbstractButton*)));
    db = database;
    uKey = Key;
}

rightDialog::~rightDialog()
{
    delete ui;
}

void rightDialog::boxClicked(QAbstractButton *button)
{
    if ((QPushButton*)button == ui->buttonBox->button(QDialogButtonBox::Ok)) {
        qDebug() << "ok button";
        emit rejected();
    } else {
        qDebug() << "cancel button";
        emit rejected();
    }
}

void rightDialog::setData()
{
    data.append(ui->lineEdit->text());                              data.append(ui->lineEdit_2->text());
    data.append(QString::number(ui->comboBox->currentIndex()));     data.append(QString::number(ui->comboBox_2->currentIndex()));
    data.append(QString::number(ui->comboBox_3->currentIndex()));
}
