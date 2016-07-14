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
    users.setPassword("MySql123");
    //if (!users.open("root", "MySql123")) {
    if (!users.open()) {
        QMessageBox::warning(this, tr("Невозможно открыть базу данных"), tr("Ошибка: ") + users.lastError().text());
        return;
    }
#endif

    QStringList lst = users.tables();
    foreach (QString str, lst)
        qDebug() << "Table: " << str;

//    QSqlQueryModel *model = new QSqlQueryModel;
//    model->setQuery("SELECT name, salary FROM employee");
//    model->setHeaderData(0, Qt::Horizontal, tr("Name"));
//    model->setHeaderData(1, Qt::Horizontal, tr("Salary"));

//    QTableView *view = new QTableView;
//    view->setModel(model);
//    view->show();

    //tusers = new QSqlQueryModel();//this, users);
    tusers = new QSqlTableModel(this, users);
    tusers->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//EditTriggers();
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tusers->setTable("tabusers");
    //tusers->setQuery("select * from tabusers;");

    //tusers->removeColumn(0);

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

    tusers->setSort(2, Qt::AscendingOrder);
    if (!tusers->select()) qDebug() << "error-tabusers: " << tusers->lastError().text();
    ui->tableView->setModel(tusers);

    ui->tableView->setColumnHidden(0,true);
    connect(ui->addUserAction, SIGNAL(triggered(bool)), this, SLOT(addUser()));
    connect(ui->accessRightsAction, SIGNAL(triggered(bool)), this, SLOT(accessRights()));
    connect(ui->delUserAction, SIGNAL(triggered(bool)), this, SLOT(delUser()));
//    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
//    deleteRowAction = new QAction("Удалить пользователя", ui->tableView);
//    ui->tableView->addAction(deleteRowAction);
//    deleteRowAction->setObjectName(QStringLiteral("deleteRowAction"));
//    deleteRowAction->setEnabled(false);
//    deleteRowAction->setStatusTip(QApplication::translate("User", "Удалить выделенного пользователя", 0));
//    connect(deleteRowAction, SIGNAL(triggered(bool)), deleteRowAction, SLOT(on_deleteRowAction_triggered()));

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
    qDebug() << "addUser";
}

void Admin::delUser()
{
    qDebug() << "delUser";
}

void Admin::accessRights()
{
    qDebug() << "accessRightsUser";
}
