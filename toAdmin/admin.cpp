#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent, QSqlDatabase  &db) :
    QMainWindow(parent), Transaction(db),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));

    tmUsers = new QSqlTableModel(this,  db);
    rights = new Rights(this,  db);
    tmUsers->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ui->accessRightsAction);
    this->addAction(ui->actionEsc);
    tmUsers->setTable("tabusers");

    QHeaderView *horizontalHeader = new QHeaderView(Qt::Horizontal, ui->tableView);
    ui->tableView->setHorizontalHeader(horizontalHeader);
    horizontalHeader->setSortIndicatorShown(true);
    horizontalHeader->setSectionsClickable(true);
    horizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
    if (!tmUsers->select()) {
        messageBox.warning(this, tr("Ошибка инициализации"), tmUsers->lastError().text());
        ui->addUserAction->setEnabled(false); ui->accessRightsAction->setEnabled(false); ui->delUserAction->setEnabled(false);
    }

    ui->tableView->setModel(tmUsers);
    ui->tableView->setColumnHidden(0,true);

    connect(ui->addUserAction, SIGNAL(triggered(bool)), this, SLOT(addUser()));
    connect(ui->accessRightsAction, SIGNAL(triggered(bool)), this, SLOT(accessRights()));
    connect(ui->delUserAction, SIGNAL(triggered(bool)), this, SLOT(delUser()));
    connect(ui->actionEsc, SIGNAL(triggered(bool)), this, SLOT(close()));

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
    try {
        userDialog uDialog;
        if (!uDialog.exec()) {
            ui->statusBar->showMessage("Отмена добавления пользователя", 5000);
            return;
        }
begin();
        QSqlRecord rec(tmUsers->record());
        //rec.setValue(0, lastKeyUser+1);
        for (int i=1; i<rec.count() - 1; i++)
            rec.setValue(i, uDialog.data.at(i-1));
        rec.setValue(8, uDialog.flat);
        if(!tmUsers->insertRecord(-1,rec)) throw QString("tmUsers->insertRecord(-1,rec): " + tmUsers->lastError().text());
        if(!tmUsers->select()) throw QString("tmUsers->select() 1: " + tmUsers->lastError().text());
commit();
        ui->statusBar->showMessage(tr("Добавлен новый пользователь"), 10000);
    }
    catch (const QString& error) {
rollback();
        messageBox.warning(this, tr("Ошибка при добавлении"), error);
    }
    catch (...) {
rollback();
        messageBox.warning(this, tr("Ошибка при добавлении"), tr("Операция выполнена неуспешно, повторите попытку позже"));
    }
}

void Admin::delUser()
{
    try {
        QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(1);
        if (rowsList.count() == 0) {
            messageBox.warning(this, tr("Удаление пользователя"), tr("В таблице нет выделенного пользователя"));
            return;
        }
        QString family = rowsList.at(0).data().toString();
        int uKey = ui->tableView->selectionModel()->selectedRows(0).at(0).data().toInt();
        if (QMessageBox::No == messageBox.question(this, tr("Удаление пользователя"), tr("Права доступа связанные с пользователем %1 так же будут удалены. Продолжить удаление?").arg(family), QMessageBox::Yes, QMessageBox::No)) return;
begin();
        QSqlQuery lpQuery(tmUsers->database());
        if (!lpQuery.exec("SELECT DISTINCT TabLoginpassword_idtabloginpassword FROM tabaccessrights WHERE TabUsers_idTabUsers = " + QString::number(uKey) + ";")) {
            ui->statusBar->showMessage("Ошибка при удалении: " + lpQuery.lastError().text());
            throw QString("Select 1u: " + lpQuery.lastError().text());
        }
        QSqlQuery delQuery(tmUsers->database());
        if (!delQuery.exec("DELETE FROM tabaccessrights WHERE TabUsers_idTabUsers = " + QString::number(uKey) + ";")) {
            ui->statusBar->showMessage("Ошибка при удалении: " + delQuery.lastError().text());
            throw QString("Select 2u: " + delQuery.lastError().text());
        }

        LP lp(0, tmUsers->database(), "", "", 0);
        while (lpQuery.next()) {
            lp.prevLpID = lpQuery.value(0).toInt();
            lp.delPrevLP();
        }
        //-----------------------------------------------?????????????????????????----------------------------------------
        bool b = tmUsers->removeRow(rowsList.at(0).row());
        if(!tmUsers->select()) throw QString("tmUsers->select() 2: " + tmUsers->lastError().text());
commit();
        if(b)   ui->statusBar->showMessage(tr("Пользователь %1 удален").arg(family), 5000);
        else    ui->statusBar->showMessage(tr("%1: права удалены, пользователь задействован в тестах или в сеансах испытаний").arg(family), 5000);
    }
    catch (const QString& error) {
rollback();
        messageBox.warning(this, tr("Ошибка при удалении"), error);
    }
    catch (...) {
rollback();
        messageBox.warning(this, tr("Ошибка при удалении"), tr("Операция выполнена неуспешно, повторите попытку позже"));
    }
}

void Admin::accessRights()
{
    try {
        QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(0);
        if (rowsList.count() == 0) {
            messageBox.warning(this, tr("Редактирование прав пользователя"), tr("В таблице нет выделенного пользователя"));
            return;
        }
        int uKey = rowsList.at(0).data().toInt();
        QString uName = ui->tableView->selectionModel()->selectedRows(1).at(0).data().toString() + " " +
                ui->tableView->selectionModel()->selectedRows(2).at(0).data().toString() + " " +
                ui->tableView->selectionModel()->selectedRows(3).at(0).data().toString();
begin();
        rights->init(uKey, uName);
commit();
    }
    catch (const QString& error) {
rollback();
        messageBox.warning(this, tr("Ошибка прав доступа"), error);
    }
    catch (...) {
rollback();
        messageBox.warning(this, tr("Ошибка прав доступа"), tr("Операция выполнена неуспешно, повторите попытку позже"));
    }
}
