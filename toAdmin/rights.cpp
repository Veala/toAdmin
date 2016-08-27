/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "rights.h"
#include "ui_rights.h"

Rights::Rights(QWidget *parent, QSqlDatabase &database) :
    QMainWindow(parent), Transaction(database),
    ui(new Ui::Rights)
{
    ui->setupUi(this);
    setFixedWidth(width());
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));

    //---------------------------------------access rights---------------------------
    tmRights = new QSqlRelationalTableModel(this, *db);

    tmRights->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->addAction(ui->actionEsc);
    tmRights->setTable("tabaccessrights");

    tmRights->setRelation(2, QSqlRelation("tabtestkinds", "idTabTestKinds", "nameTestKind"));
    tmRights->setRelation(3, QSqlRelation("tabtypeproducts", "idTabTypeProducts", "nameTypeProduct"));
    tmRights->setRelation(5, QSqlRelation("tabauthoritykinds", "idTabAuthorityKinds", "AuthorityKind"));
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    QHeaderView *horizontalHeader = new QHeaderView(Qt::Horizontal, ui->tableView);
    horizontalHeader->setToolTip(tr("Сортировка(активация)"));
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

    connect(ui->addRightsAction, SIGNAL(triggered(bool)), this, SLOT(addRights()));
    connect(ui->delRightsAction, SIGNAL(triggered(bool)), this, SLOT(delRights()));
    connect(ui->actionEsc, SIGNAL(triggered(bool)), this, SLOT(close()));

    //---------------------------------------status bar---------------------------
    ui->statusbar->setStyleSheet("background-color: rgb(255, 255, 255); border-top: 1px solid black;");
    ui->statusbar->setSizeGripEnabled(false);
}

Rights::~Rights()
{
    delete ui;
}

void Rights::init(int Key, QString uName)
{
    uKey = Key;
    tmRights->setFilter("TabUsers_idTabUsers = " + QString::number(uKey));
    if(!tmRights->select()) rollback(QString("tmRights->select() 1: " + tmRights->lastError().text())); //верно - throw уходит дальше
    setWindowTitle(uName);
    show();
}

void Rights::sorting(int column, Qt::SortOrder sortOrder)
{
    tmRights->sort(column, sortOrder);
}

void Rights::addRights()
{
    try {
begin();
        QSqlQuery testKindsQuery(*db);
        QSqlQuery typeProductsQuery(*db);
        QSqlQuery authorityKindsQuery(*db);
        if (!testKindsQuery.exec("SELECT * FROM tabtestkinds;"))
            rollback(QString("Select 1r: " + testKindsQuery.lastError().text()));
        if (!typeProductsQuery.exec("SELECT * FROM tabtypeproducts;"))
            rollback(QString("Select 2r: " + typeProductsQuery.lastError().text()));
        if (!authorityKindsQuery.exec("SELECT * FROM tabauthoritykinds;"))
            rollback(QString("Select 3r: " + authorityKindsQuery.lastError().text()));
        QStringList nameTestKinds, nameTypeProducts, nameAuthorityKinds;
        QVector<int> idTestKinds, idTypeProducts, idAuthorityKinds;
        for (int i=0; i<testKindsQuery.size(); i++) { testKindsQuery.next(); nameTestKinds.append(testKindsQuery.value(1).toString()); idTestKinds.append(testKindsQuery.value(0).toInt()); }
        for (int i=0; i<typeProductsQuery.size(); i++) { typeProductsQuery.next(); nameTypeProducts.append(typeProductsQuery.value(1).toString()); idTypeProducts.append(typeProductsQuery.value(0).toInt()); }
        for (int i=0; i<authorityKindsQuery.size(); i++) { authorityKindsQuery.next(); nameAuthorityKinds.append(authorityKindsQuery.value(1).toString()); idAuthorityKinds.append(authorityKindsQuery.value(0).toInt()); }
        QVector<QStringList> list;
        list.append(nameTestKinds); list.append(nameTypeProducts); list.append(nameAuthorityKinds);

        rightDialog rDialog(0, list);
        if (!rDialog.exec()) {
rollback(QString("standard situation"));
            ui->statusbar->showMessage("Отмена добавления права", 5000);
            return;
        }

        QSqlRecord rec(tmRights->record());
        //    qDebug() << idTestKinds.at(rDialog.data.at(2).toInt());
        //    qDebug() << idTypeProducts.at(rDialog.data.at(3).toInt());
        //    qDebug() << idAuthorityKinds.at(rDialog.data.at(4).toInt());

        //    rec.setValue(0, lastKeyAccessRights+1);
        rec.setValue(1, uKey);
        rec.setValue(2, idTestKinds.at(rDialog.data.at(0).toInt()));
        rec.setValue(3, idTypeProducts.at(rDialog.data.at(1).toInt()));
        rec.setValue(4, uKey);
        rec.setValue(5, idAuthorityKinds.at(rDialog.data.at(2).toInt()));

        if(!tmRights->insertRecord(-1,rec)) rollback(QString("Insert 0: tmRights->insertRecord(-1,rec)"));
        if(!tmRights->select()) rollback(QString("tmRights->select() 1: " + tmRights->lastError().text()));
commit();
        ui->statusbar->showMessage(tr("Добавлено право доступа"), 10000);
    }
    catch (const trException& err) {
        error(err, tr("Ошибка при добавлении"));
    }
    catch (...) {
        error(trException(OTHER_ERR, tr("Неизвестная ошибка")), tr("Ошибка при добавлении"));
    }
}

void Rights::delRights()
{
    try {
        QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(1);
        if (rowsList.count() == 0) {
            messageBox.warning(this, tr("Удаление права доступа"), tr("В таблице нет выделенного права доступа"));
            return;
        }
        if (QMessageBox::No == messageBox.question(this, tr("Удаление права доступа"), tr("Право доступа будет удалено. Продолжить удаление?"), QMessageBox::Yes, QMessageBox::No)) {
            ui->statusbar->showMessage(tr("Отмена удаления права"), 5000);
            return;
        }

begin();
        if (!tmRights->removeRow(rowsList.at(0).row())) rollback(QString("Error: tmRights->removeRow(rowsList.at(0).row()): " + tmRights->lastError().text()));
        if (!tmRights->select()) rollback(QString("Error: Select logPas 3: " + tmRights->lastError().text()));
commit();
        ui->statusbar->showMessage(tr("Право доступа удалено"), 5000);
    }
    catch (const trException& err) {
        error(err, tr("Ошибка удаления прав"));
    }
    catch (...) {
        error(trException(OTHER_ERR, tr("Неизвестная ошибка")), tr("Ошибка удаления прав"));
    }
}

void Rights::error(const Transaction::trException err, QString name)
{
    switch (err.type) {
    case BEGIN_ERR:
        ui->statusbar->showMessage("Ошибка инициализации транзакции");
        break;
    case ROLLBACK_OK_ERR:
        ui->statusbar->showMessage("Откат транзакции завершен успешно");
        break;
    case ROLLBACK_CRITICAL_ERR:
        ui->addRightsAction->setEnabled(false); ui->delRightsAction->setEnabled(false);
        ui->statusbar->showMessage("Откат транзакции завершен неуспешно");
        emit sError(err, name);
        break;
    case OTHER_ERR:
        ui->addRightsAction->setEnabled(false); ui->delRightsAction->setEnabled(false);
        ui->statusbar->showMessage(err.data);
        emit sError(err, name);
        break;
    }
    messageBox.warning(this, name, err.data + tr("\nПовторите попытку позже"));
}
