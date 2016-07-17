#include "rights.h"
#include "ui_rights.h"

Rights::Rights(QWidget *parent, QSqlDatabase &db) :
    QMainWindow(parent),
    ui(new Ui::Rights)
{
    ui->setupUi(this);

    //---------------------------------------access rights---------------------------
    tmRights = new QSqlRelationalTableModel(this, db);

    tmRights->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ui->logPasAction);
    tmRights->setTable("tabaccessrights");

    tmRights->setRelation(2, QSqlRelation("tabtestkinds", "idTabTestKinds", "nameTestKind"));
    tmRights->setRelation(3, QSqlRelation("tabtypeproducts", "idTabTypeProducts", "nameTypeProduct"));
    tmRights->setRelation(5, QSqlRelation("tabauthoritykinds", "idTabAuthorityKinds", "AuthorityKind"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    QHeaderView *horizontalHeader = new QHeaderView(Qt::Horizontal, ui->tableView);
    ui->tableView->setHorizontalHeader(horizontalHeader);
    horizontalHeader->setSortIndicatorShown(true);
    horizontalHeader->setSectionsClickable(true);
    horizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(horizontalHeader,SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this, SLOT(sorting(int,Qt::SortOrder)));
    tmRights->setHeaderData(0, Qt::Horizontal, tr("ИД"));
    tmRights->setHeaderData(1, Qt::Horizontal, tr("Логин-Пароль"));
    tmRights->setHeaderData(2, Qt::Horizontal, tr("Вид тестов"));
    tmRights->setHeaderData(3, Qt::Horizontal, tr("Тип изделия"));
    tmRights->setHeaderData(4, Qt::Horizontal, tr("Пользователи"));
    tmRights->setHeaderData(5, Qt::Horizontal, tr("Вид авторизации"));

    ui->tableView->setModel(tmRights);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(1,true);
    ui->tableView->setColumnHidden(4,true);
//    ui->tableView->resizeColumnsToContents();
//    ui->tableView->resizeRowsToContents();

    connect(ui->addRightsAction, SIGNAL(triggered(bool)), this, SLOT(addRights()));
    connect(ui->delRightsAction, SIGNAL(triggered(bool)), this, SLOT(delRights()));


    //---------------------------------------login password---------------------------
    lpView = new QTableView(0);
    tmLogPas = new QSqlTableModel(lpView, db);

    tmLogPas->setEditStrategy(QSqlTableModel::OnFieldChange);
    lpView->setSelectionBehavior(QAbstractItemView::SelectItems);
    lpView->setSelectionMode(QAbstractItemView::SingleSelection);
    lpView->setWindowModality(Qt::ApplicationModal);
    lpView->setToolTip(tr("Редактировать поле"));
    lpView->resize(200,50);
    tmLogPas->setTable("tabloginpassword");

    QHeaderView *horizontalHeader_lp = new QHeaderView(Qt::Horizontal, lpView);
    lpView->setHorizontalHeader(horizontalHeader_lp);
    horizontalHeader_lp->setSectionResizeMode(QHeaderView::ResizeToContents);
    //lpView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tmLogPas->setHeaderData(0, Qt::Horizontal, tr("ИД"));
    tmLogPas->setHeaderData(1, Qt::Horizontal, tr("Логин"));
    tmLogPas->setHeaderData(2, Qt::Horizontal, tr("Пароль"));
    lpView->verticalHeader()->setHidden(true);

    lpView->setModel(tmLogPas);
    lpView->setColumnHidden(0,true);

    connect(ui->logPasAction, SIGNAL(triggered(bool)), this, SLOT(logPas()));

    //---------------------------------------status bar---------------------------
    ui->statusbar->setStyleSheet("background-color: rgb(255, 255, 255); border-top: 1px solid black;");
    ui->statusbar->setSizeGripEnabled(false);

}

Rights::~Rights()
{
    delete lpView;
    delete ui;
}

void Rights::init(int uKey, QString uName)
{
    tmRights->setFilter("TabUsers_idTabUsers = " + QString::number(uKey));
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
//    QSqlRecord rec(tmRights->record());
//    rec.setValue(0, 3);
//    for (int i=1; i<rec.count() - 1; i++)
//        rec.setValue(i, tmUsers->headerData(i, Qt::Horizontal));
//    rec.setValue(8, 0);
//    tmUsers->insertRecord(-1,rec);
//    ui->statusBar->showMessage(tr("В конец таблицы добавлено поле для редактирования(Фамилия, Имя, ...)"), 10000);
}

void Rights::logPas()
{
    QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(1);
    if (rowsList.count() == 0) {
        QMessageBox::warning(this, tr("Логин-пароль"), tr("В таблице нет выделенного поля"));
        return;
    }
    int lpKey = rowsList.at(0).data().toInt();
    QString numStr = "Строка №" + QString::number(rowsList.at(0).row() + 1);
    tmLogPas->setFilter("idTabLoginPassword = " + QString::number(lpKey));
    lpView->setWindowTitle(numStr);
    tmLogPas->select();
    lpView->show();
}

void Rights::delRights()
{
    QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(0);
    if (rowsList.count() == 0) {
        QMessageBox::warning(this, tr("Удаление права доступа"), tr("В таблице нет выделенного права доступа"));
        return;
    }
    if (QMessageBox::No == QMessageBox::question(this, tr("Удаление права доступа"), tr("Право доступа будет удалено. Продолжить удаление?"), QMessageBox::Yes, QMessageBox::No)) return;

    tmRights->removeRow(rowsList.at(0).row());
    tmRights->select();
    ui->statusbar->showMessage(tr("Право доступа удалено"), 5000);
}
