#include "admin.h"
#include "ui_admin.h"

#define debug_1

Admin::Admin(QWidget *parent) ://, QSqlDatabase users) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

#ifdef debug_1
    //users = QSqlDatabase::addDatabase("QMYSQL");// new QSqlDatabase();
    users = QSqlDatabase::addDatabase("QMYSQL");
    users.setDatabaseName("BDBIVKM");
    users.setHostName("localhost");
    users.setPort(3306);
    users.setUserName("root");
    users.setPassword("MySql123");
    //if (!users.open("root", "MySql123"))
    if (!users.open())
        QMessageBox::warning(this, tr("Невозможно открыть базу данных"), tr("Ошибка: ") + users.lastError().text());
#endif

    QStringList lst = users.tables();
    foreach (QString str, lst) {
        qDebug() << "Table: " << str;
    }

    tusers = new QSqlTableModel(this, users);

    tusers->setTable("tabusers");
    if (!tusers->select()) qDebug() << "error-tabusers: " << tusers->lastError().text();
    tusers->setEditStrategy(QSqlTableModel::OnRowChange);
    ui->tableView->setModel(tusers);


}

Admin::~Admin()
{
    delete ui;
}
