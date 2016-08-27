/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "userdialog.h"
#include "ui_userdialog.h"

userDialog::userDialog(QWidget *parent, QSqlDatabase &database) :
    QDialog(parent), Transaction(database),
    ui(new Ui::userDialog)
{
    ui->setupUi(this);
    setFixedSize(size());
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("ОК"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Отмена"));
    QRegExp urx("[0-9A-Za-zА-Яа-я-]+");
    QRegExp lprx("[0-9A-Za-z]+");
    uValidator = new QRegExpValidator(urx,this);
    lpValidator = new QRegExpValidator(lprx,this);
    ui->lineEdit->setValidator(uValidator);
    ui->lineEdit_2->setValidator(uValidator);
    ui->lineEdit_3->setValidator(uValidator);
    ui->lineEdit_8->setValidator(lpValidator);
    ui->lineEdit_9->setValidator(lpValidator);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(setData()));
}

userDialog::~userDialog()
{
    delete ui;
}

void userDialog::setData()
{
    try {
        if (ui->lineEdit_8->text().length() < 4)    { messageBox.warning(this,tr("Синтаксическия ошибка"),tr("Логин должен быть не менее 4 символов"));     return; }
        if (ui->lineEdit_9->text().length() < 6)    { messageBox.warning(this,tr("Синтаксическия ошибка"),tr("Пароль должен быть не менее 6 символов"));    return; }
        if ((ui->lineEdit->text().length() < 3)   ||
            (ui->lineEdit_2->text().length() < 3) ||
            (ui->lineEdit_2->text().length() < 3))
        {
            if (QMessageBox::No == messageBox.information(this,tr("Синтаксическая неточность"),tr("Фамилия, имя, отчество: в поле(-ях) менее 3-х символов. Продолжить?"),QMessageBox::Yes,QMessageBox::No))
                return;
        }

        QSqlQuery p(*db);
        if(!p.exec(QString("SELECT * FROM tabloginpassword WHERE login = \"%1\";").arg(ui->lineEdit_8->text())))
            rollback(QString("SELECT UserDialog: " + p.lastError().text()));
        if (p.size() >= 1) { messageBox.warning(this, tr("Ошибка добавления пользователя"), tr("Данный логин занят другим пользователем")); return; }
        if (!p.exec(QString("INSERT INTO tabloginpassword (login, password) VALUES ('%1', '%2');").arg(ui->lineEdit_8->text(), ui->lineEdit_9->text())))
            rollback(QString("INSERT UserDialog: " + p.lastError().text()));

        data.append(ui->lineEdit->text());     data.append(ui->lineEdit_2->text());
        data.append(ui->lineEdit_3->text());   data.append(ui->lineEdit_4->text());
        data.append(ui->lineEdit_5->text());   data.append(ui->lineEdit_6->text());
        data.append(ui->lineEdit_7->text());   flat = ui->spinBox->value();

        accept();
    }
    catch (const trException& error) {
        trError.type = error.type;
        trError.data = error.data;
        reject();
    }
    catch (...) {
        messageBox.warning(this, tr("Ошибка добавления пользователя"), tr("Операция выполнена неуспешно, повторите попытку позже"));
        reject();
    }
}
