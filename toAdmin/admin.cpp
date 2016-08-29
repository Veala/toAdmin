/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent, QSqlDatabase &database) :
    QMainWindow(parent), Transaction(database),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));

    tmUsers = new QSqlTableModel(this,  *db);
    rights = new Rights(this,  *db);
    connect(rights, SIGNAL(sError(trException,QString)), this, SLOT(error(trException,QString)));

    tmUsers->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ui->accessRightsAction);
    ui->tableView->addAction(ui->logPasAction);
    this->addAction(ui->actionEsc);
    tmUsers->setTable("tabusers");

    QHeaderView *horizontalHeader = new QHeaderView(Qt::Horizontal, ui->tableView);
    horizontalHeader->setToolTip(tr("Сортировка(активация)"));
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
    connect(ui->logPasAction, SIGNAL(triggered(bool)), this, SLOT(logPas()));
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
begin();
        userDialog uDialog(0, *db);
        if (!uDialog.exec()) {
            if (uDialog.trError.type == NO_ERR) {
rollback(QString("standard situation"));
                ui->statusBar->showMessage("Отмена добавления пользователя", 5000);
                return;
            } else {
                throw uDialog.trError;
            }
        }
        QSqlRecord rec(tmUsers->record());
        //rec.setValue(0, lastKeyUser+1);
        for (int i=1; i<rec.count() - 1; i++)
            rec.setValue(i, uDialog.data.at(i-1));
        rec.setValue(8, uDialog.flat);
        if(!tmUsers->insertRecord(-1,rec)) rollback(QString("tmUsers->insertRecord(-1,rec): " + tmUsers->lastError().text()));
        if(!tmUsers->select()) rollback(QString("tmUsers->select() 1: " + tmUsers->lastError().text()));

        int lastUID = tmUsers->query().lastInsertId().toInt();
        for (int i=0; i<tmUsers->rowCount(); i++)   if (tmUsers->index(i,0).data().toInt() == lastUID) { ui->tableView->selectRow(i); break; }
commit();
        ui->statusBar->showMessage(tr("Добавлен новый пользователь"), 10000);
        accessRights();
    }
    catch (const trException& err) {
        error(err, tr("Ошибка при добавлении"));
    }
    catch (...) {
        error(trException(OTHER_ERR, tr("Неизвестная ошибка")), tr("Ошибка при добавлении"));
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
        if (QMessageBox::No == messageBox.question(this, tr("Удаление пользователя"), tr("Права доступа связанные с пользователем %1 так же будут удалены. Продолжить удаление?").arg(family), QMessageBox::Yes, QMessageBox::No)) {
            ui->statusBar->showMessage(tr("Отмена удаления пользователя"), 5000);
            return;
        }
begin();
        QSqlQuery lpQuery(*db);
        if (!lpQuery.exec("SELECT DISTINCT TabLoginpassword_idtabloginpassword FROM tabaccessrights WHERE TabUsers_idTabUsers = " + QString::number(uKey) + ";")) {
            ui->statusBar->showMessage("Ошибка при удалении: " + lpQuery.lastError().text());
            rollback(QString("Select 1u: " + lpQuery.lastError().text()));
        }
        QSqlQuery delQuery(*db);
        if (!delQuery.exec("DELETE FROM tabaccessrights WHERE TabUsers_idTabUsers = " + QString::number(uKey) + ";")) {
            ui->statusBar->showMessage("Ошибка при удалении: " + delQuery.lastError().text());
            rollback(QString("Select 2u: " + delQuery.lastError().text()));
        }
        if (!delQuery.exec("DELETE FROM tabloginpassword WHERE idTabLoginPassword = " + QString::number(uKey) + ";")) {
            ui->statusBar->showMessage("Ошибка при удалении: " + delQuery.lastError().text());
            rollback(QString("Select 3u: " + delQuery.lastError().text()));
        }

        if(!tmUsers->removeRow(rowsList.at(0).row())) rollback(QString("tmUsers->removeRow: " + tmUsers->lastError().text()));
        if(!tmUsers->select()) rollback(QString("tmUsers->select() 2: " + tmUsers->lastError().text()));
commit();
        ui->statusBar->showMessage(tr("Пользователь %1 и его права удалены").arg(family), 5000);
    }
    catch (const trException& err) {
        error(err, tr("Ошибка при удалении"));
    }
    catch (...) {
        error(trException(OTHER_ERR, tr("Неизвестная ошибка")), tr("Ошибка при удалении"));
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
    catch (const trException& err) {
        error(err, tr("Ошибка прав доступа"));
    }
    catch (...) {
        error(trException(OTHER_ERR, tr("Неизвестная ошибка")), tr("Ошибка прав доступа"));
    }
}

void Admin::logPas()
{
    try {
        QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows();
        if (rowsList.count() == 0) {
            messageBox.warning(this, tr("Логин-пароль"), tr("В таблице нет выделенного поля"));
            return;
        }
        int uID = rowsList.at(0).data().toInt();
        //qDebug() << "uID:" << uID;
        QString surname = ui->tableView->selectionModel()->selectedRows(1).at(0).data().toString();
begin();
        QSqlQuery qlp(*db);
        if(!qlp.exec(QString("SELECT * FROM tabloginpassword WHERE idTabLoginPassword = %1;").arg(QString::number(uID))))
            rollback(QString("Select logPas 1: " + qlp.lastError().text()));
        qlp.next();

        lpDialog lpdialog(0, qlp.value(1).toString(), qlp.value(2).toString(), *db);
        lpdialog.setWindowTitle(surname);
        lpdialog.lpID = uID;

        if (lpdialog.exec()) {
commit();
            ui->statusBar->showMessage(tr("Изменения логина и пароля завершены успешно"), 10000);
        } else {
            if (lpdialog.trError.type == NO_ERR) {
rollback(QString("standard situation"));
                ui->statusBar->showMessage("Отмена редактирования логина и пароля", 10000);
                return;
            } else {
                throw lpdialog.trError;
            }
        }
    }
    catch (const trException& err) {
        error(err, tr("Ошибка \"логин-пароль\""));
    }
    catch (...) {
        error(trException(OTHER_ERR, tr("Неизвестная ошибка")), tr("Ошибка \"логин-пароль\""));
    }
}

void Admin::error(const trException err, QString name)
{
    switch (err.type) {
    case BEGIN_ERR:
        ui->statusBar->showMessage("Ошибка инициализации транзакции");
        break;
    case ROLLBACK_OK_ERR:
        ui->statusBar->showMessage("Откат транзакции завершен успешно");
        break;
    case ROLLBACK_CRITICAL_ERR:
        ui->addUserAction->setEnabled(false); ui->accessRightsAction->setEnabled(false);
        ui->delUserAction->setEnabled(false); ui->logPasAction->setEnabled(false);
        ui->statusBar->showMessage("Откат транзакции завершен неуспешно");
        emit sError(err.data);
        break;
    case OTHER_ERR:
        ui->addUserAction->setEnabled(false); ui->accessRightsAction->setEnabled(false);
        ui->delUserAction->setEnabled(false); ui->logPasAction->setEnabled(false);
        ui->statusBar->showMessage(err.data);
        emit sError(err.data);
        break;
    }
    if (sender()->objectName() == "Rights") return;
    messageBox.warning(this, name, err.data + tr("\nПовторите попытку позже"));
}
