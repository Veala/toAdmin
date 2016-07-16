#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent, QSqlDatabase  &db) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    tmUsers = new QSqlTableModel(this,  db);
    rights = new Rights(this,  db);
    tmUsers->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//EditTriggers();
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tmUsers->setTable("tabusers");

    QHeaderView *horizontalHeader = new QHeaderView(Qt::Horizontal, ui->tableView);
    ui->tableView->setHorizontalHeader(horizontalHeader);
    horizontalHeader->setSortIndicatorShown(true);
    horizontalHeader->setSectionsClickable(true);
    connect(horizontalHeader,SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)),this, SLOT(sorting(int,Qt::SortOrder)));
    tmUsers->setHeaderData(0, Qt::Horizontal, tr("ИД"));
    tmUsers->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    tmUsers->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    tmUsers->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
    tmUsers->setHeaderData(4, Qt::Horizontal, tr("Телефон"));
    tmUsers->setHeaderData(5, Qt::Horizontal, tr("e-mail"));
    tmUsers->setHeaderData(6, Qt::Horizontal, tr("Сектор"));
    tmUsers->setHeaderData(7, Qt::Horizontal, tr("Должность"));
    tmUsers->setHeaderData(8, Qt::Horizontal, tr("Комната"));

    tmUsers->setSort(1, Qt::AscendingOrder);
    if (!tmUsers->select()) qDebug() << "error-tabusers: " << tmUsers->lastError().text();

    ui->tableView->setModel(tmUsers);
    ui->tableView->setColumnHidden(0,true);

    connect(ui->addUserAction, SIGNAL(triggered(bool)), this, SLOT(addUser()));
    connect(ui->accessRightsAction, SIGNAL(triggered(bool)), this, SLOT(accessRights()));
    connect(ui->delUserAction, SIGNAL(triggered(bool)), this, SLOT(delUser()));

    ui->statusBar->setStyleSheet("background-color: rgb(255, 255, 255); border-top: 1px solid black;");
    ui->statusBar->setSizeGripEnabled(false);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::sorting(int column, Qt::SortOrder sortOrder)
{
    tmUsers->sort(column, sortOrder);
}

void Admin::addUser()
{
    QSqlRecord rec(tmUsers->record());
    rec.setValue(0, 5);
    for (int i=1; i<rec.count() - 1; i++)
        rec.setValue(i, tmUsers->headerData(i, Qt::Horizontal));
    rec.setValue(8, 0);
    tmUsers->insertRecord(-1,rec);
    ui->statusBar->showMessage(tr("В конец таблицы добавлено поле для редактирования(Фамилия, Имя, ...)"), 10000);
}

void Admin::delUser()
{    
    QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(1);
    if (rowsList.count() == 0) {
        QMessageBox::warning(this, tr("Удаление пользователя"), tr("В таблице нет выделенного пользователя"));
        return;
    }
    QString family = rowsList.at(0).data().toString();
    int uKey = ui->tableView->selectionModel()->selectedRows(0).at(0).data().toInt();
    if (QMessageBox::No == QMessageBox::question(this, tr("Удаление пользователя"), tr("Права доступа связанные с пользователем %1 так же будут удалены. Продолжить удаление?").arg(family), QMessageBox::Yes, QMessageBox::No)) return;

    QSqlQuery delQuery(tmUsers->database());
    if (!delQuery.exec("DELETE FROM tabaccessrights WHERE TabUsers_idTabUsers = " + QString::number(uKey) + ";")) {
        ui->statusBar->showMessage("Ошибка при удалении: " + delQuery.lastError().text());
        return;
    }
    tmUsers->removeRow(rowsList.at(0).row());
    tmUsers->select();
    ui->statusBar->showMessage(tr("Пользователь %1 удален").arg(family), 5000);
}

void Admin::accessRights()
{
    QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(0);
    if (rowsList.count() == 0) {
        QMessageBox::warning(this, tr("Редактирование прав пользователя"), tr("В таблице нет выделенного пользователя"));
        return;
    }
    int uKey = rowsList.at(0).data().toInt();
    QString uName = ui->tableView->selectionModel()->selectedRows(1).at(0).data().toString() + " " +
                    ui->tableView->selectionModel()->selectedRows(2).at(0).data().toString() + " " +
                    ui->tableView->selectionModel()->selectedRows(3).at(0).data().toString();
    rights->init(uKey, uName);
}
