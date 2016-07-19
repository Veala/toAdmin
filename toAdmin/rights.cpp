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
    tmRights->setHeaderData(2, Qt::Horizontal, tr("Вид испытаний"));
    tmRights->setHeaderData(3, Qt::Horizontal, tr("Тип изделия"));
    tmRights->setHeaderData(4, Qt::Horizontal, tr("Пользователи"));
    tmRights->setHeaderData(5, Qt::Horizontal, tr("Вид полномочий"));

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

void Rights::init(int Key, QString uName)
{
    uKey = Key;
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
    QSqlQuery testKindsQuery(tmRights->database());
    QSqlQuery typeProductsQuery(tmRights->database());
    QSqlQuery authorityKindsQuery(tmRights->database());
    if (!testKindsQuery.exec("SELECT * FROM tabtestkinds;")) {
        ui->statusbar->showMessage("Ошибка при добавлении пользователя: " + testKindsQuery.lastError().text());
        return;
    }
    if (!typeProductsQuery.exec("SELECT * FROM tabtypeproducts;")) {
        ui->statusbar->showMessage("Ошибка при добавлении пользователя: " + typeProductsQuery.lastError().text());
        return;
    }
    if (!authorityKindsQuery.exec("SELECT * FROM tabauthoritykinds;")) {
        ui->statusbar->showMessage("Ошибка при добавлении пользователя: " + authorityKindsQuery.lastError().text());
        return;
    }
    QStringList nameTestKinds, nameTypeProducts, nameAuthorityKinds;
    QVector<int> idTestKinds, idTypeProducts, idAuthorityKinds;
    for (int i=0; i<testKindsQuery.size(); i++) { testKindsQuery.next(); nameTestKinds.append(testKindsQuery.value(1).toString()); idTestKinds.append(testKindsQuery.value(0).toInt()); }
    for (int i=0; i<typeProductsQuery.size(); i++) { typeProductsQuery.next(); nameTypeProducts.append(typeProductsQuery.value(1).toString()); idTypeProducts.append(typeProductsQuery.value(0).toInt()); }
    for (int i=0; i<authorityKindsQuery.size(); i++) { authorityKindsQuery.next(); nameAuthorityKinds.append(authorityKindsQuery.value(1).toString()); idAuthorityKinds.append(authorityKindsQuery.value(0).toInt()); }
    QVector<QStringList> list;
    list.append(nameTestKinds); list.append(nameTypeProducts); list.append(nameAuthorityKinds);

    rightDialog rDialog(0, list, uKey, tmRights->database());
    if (!rDialog.exec()) {
        ui->statusbar->showMessage("Отмена добавления пользователя", 5000);
        return;
    }

    QSqlRecord rec(tmRights->record());
    qDebug() << idTestKinds.at(rDialog.data.at(2).toInt());
    qDebug() << idTypeProducts.at(rDialog.data.at(3).toInt());
    qDebug() << idAuthorityKinds.at(rDialog.data.at(4).toInt());
    //rec.setValue(0, lastKeyAccessRights+1);
    rec.setValue(1, 1);
    rec.setValue(2, idTestKinds.at(rDialog.data.at(2).toInt()));
    rec.setValue(3, idTypeProducts.at(rDialog.data.at(3).toInt()));
    rec.setValue(4, uKey);
    rec.setValue(5, idAuthorityKinds.at(rDialog.data.at(4).toInt()));


    tmRights->insertRecord(-1,rec);
    tmRights->select();
    ui->statusbar->showMessage(tr("Добавлено право пользователя"), 10000);
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
