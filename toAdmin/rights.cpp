#include "rights.h"
#include "ui_rights.h"

Rights::Rights(QWidget *parent, QSqlDatabase &db) :
    QMainWindow(parent),
    ui(new Ui::Rights)
{
    ui->setupUi(this);

    tmLogPas = new QSqlTableModel(this, db);
    tmRights = new QSqlRelationalTableModel(this, db);

    tmRights->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tmRights->setTable("tabaccessrights");

    tmLogPas->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView_lp->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView_lp->setSelectionMode(QAbstractItemView::SingleSelection);
    tmLogPas->setTable("tabloginpassword");

    tmRights->setRelation(2, QSqlRelation("tabtestkinds", "idTabTestKinds", "nameTestKind"));
    tmRights->setRelation(3, QSqlRelation("tabtypeproducts", "idTabTypeProducts", "nameTypeProduct"));
    tmRights->setRelation(5, QSqlRelation("tabauthoritykinds", "idTabAuthorityKinds", "AuthorityKind"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    QHeaderView *horizontalHeader = new QHeaderView(Qt::Horizontal, ui->tableView);
    ui->tableView->setHorizontalHeader(horizontalHeader);
    horizontalHeader->setSortIndicatorShown(true);
    horizontalHeader->setSectionsClickable(true);
    connect(horizontalHeader,SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this, SLOT(sorting(int,Qt::SortOrder)));
//    connect(ui->tableView, SIGNAL())
    tmRights->setHeaderData(0, Qt::Horizontal, tr("ИД"));
    tmRights->setHeaderData(1, Qt::Horizontal, tr("Логин-Пароль"));
    tmRights->setHeaderData(2, Qt::Horizontal, tr("Вид тестов"));
    tmRights->setHeaderData(3, Qt::Horizontal, tr("Тип изделия"));
    tmRights->setHeaderData(4, Qt::Horizontal, tr("Пользователи"));
    tmRights->setHeaderData(5, Qt::Horizontal, tr("Вид авторизации"));

    QHeaderView *horizontalHeader_lp = new QHeaderView(Qt::Horizontal, ui->tableView_lp);
    ui->tableView_lp->setHorizontalHeader(horizontalHeader_lp);
    tmLogPas->setHeaderData(0, Qt::Horizontal, tr("ИД"));
    tmLogPas->setHeaderData(1, Qt::Horizontal, tr("Логин"));
    tmLogPas->setHeaderData(2, Qt::Horizontal, tr("Пароль"));
    ui->tableView_lp->verticalHeader()->setHidden(true);

    ui->tableView->setModel(tmRights);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(1,true);
    ui->tableView->setColumnHidden(4,true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    ui->tableView_lp->setModel(tmLogPas);
    ui->tableView_lp->setColumnHidden(0,true);
    ui->tableView_lp->resizeColumnsToContents();
    ui->tableView_lp->resizeRowsToContents();

    connect(ui->addRightsAction, SIGNAL(triggered(bool)), this, SLOT(addRights()));
    connect(ui->delRightsAction, SIGNAL(triggered(bool)), this, SLOT(delRights()));

    ui->statusbar->setStyleSheet("background-color: rgb(255, 255, 255); border-top: 1px solid black;");
    ui->statusbar->setSizeGripEnabled(false);

}

Rights::~Rights()
{
    delete ui;
}

void Rights::init(int uKey, QString uName)
{
    tmRights->setFilter("TabUsers_idTabUsers = " + QString::number(uKey));
//    tmRights->setQuery(QSqlQuery("SELECT *, tabaccesrights.TabLoginPassword_idTabLoginPassword"
//                                 " FROM tabaccessrights WHERE TabUsers_idTabUsers = "
//                                 + QString::number(uKey) + ";", tmRights->database()));
    tmRights->select();
    setWindowTitle(tr("Права доступа пользователя: ") + uName);
    show();
}

void Rights::sorting(int column, Qt::SortOrder sortOrder)
{
    tmRights->sort(column, sortOrder);
}

void Rights::addRights()
{

}

void Rights::delRights()
{

}
