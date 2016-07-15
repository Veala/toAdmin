#include "admin.h"
#include "ui_admin.h"

#define debug_1

Admin::Admin(QWidget *parent) ://, QSqlDatabase users) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

#ifdef debug_1
    users = QSqlDatabase::addDatabase("QMYSQL");
    users.setDatabaseName("BDBIVKM");
    users.setHostName("localhost");
    users.setPort(3306);
    users.setUserName("root");
    users.setPassword("MySql1234");
    if (!users.open()) {
        QMessageBox::warning(this, tr("Невозможно открыть базу данных"), tr("Ошибка: ") + users.lastError().text());
        return;
    }
#endif

    tusers = new QSqlTableModel(this, users);
    tusers->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//EditTriggers();
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tusers->setTable("tabusers");

    QHeaderView *horizontalHeader = new QHeaderView(Qt::Horizontal, ui->tableView);
    ui->tableView->setHorizontalHeader(horizontalHeader);
    horizontalHeader->setSortIndicatorShown(true);
    horizontalHeader->setSectionsClickable(true);
    connect(horizontalHeader,SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this, SLOT(sorting(int,Qt::SortOrder)));
    tusers->setHeaderData(0, Qt::Horizontal, tr("ИД"));
    tusers->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    tusers->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    tusers->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
    tusers->setHeaderData(4, Qt::Horizontal, tr("Телефон"));
    tusers->setHeaderData(5, Qt::Horizontal, tr("e-mail"));
    tusers->setHeaderData(6, Qt::Horizontal, tr("Сектор"));
    tusers->setHeaderData(7, Qt::Horizontal, tr("Должность"));
    tusers->setHeaderData(8, Qt::Horizontal, tr("Комната"));

    tusers->setSort(1, Qt::AscendingOrder);
    if (!tusers->select()) qDebug() << "error-tabusers: " << tusers->lastError().text();

    if (tusers->lastError().type() != QSqlError::NoError)
        ui->statusBar->showMessage(tusers->lastError().text(), 5000);

    ui->tableView->setModel(tusers);

    ui->tableView->setColumnHidden(0,true);
    connect(ui->addUserAction, SIGNAL(triggered(bool)), this, SLOT(addUser()));
    connect(ui->accessRightsAction, SIGNAL(triggered(bool)), this, SLOT(accessRights()));
    connect(ui->delUserAction, SIGNAL(triggered(bool)), this, SLOT(delUser()));
}

Admin::~Admin()
{
    delete ui;
}

void Admin::sorting(int column, Qt::SortOrder sortOrder)
{
    tusers->sort(column, sortOrder);
}

void Admin::addUser()
{
    QSqlRecord rec(tusers->record());
    rec.setValue(0, 5);
    for (int i=1; i<rec.count() - 1; i++)
        rec.setValue(i, tusers->headerData(i, Qt::Horizontal));
    rec.setValue(8, 0);
    tusers->insertRecord(-1,rec);
}

void Admin::delUser()
{
    QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(1);
    if (rowsList.count() == 0) {
        qDebug() << "error, no changeed rows";
        return;
    }
    tusers->removeRow(rowsList.at(0).row());
    tusers->select();
    if (tusers->lastError().type() != QSqlError::NoError)
        ui->statusBar->showMessage(tusers->lastError().text(), 5000);

}

void Admin::accessRights()
{
    qDebug() << "accessRightsUser";
}
