#include "rights.h"
#include "ui_rights.h"

Rights::Rights(QWidget *parent, QSqlDatabase &db) :
    QMainWindow(parent),
    ui(new Ui::Rights)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/img/img.png"));
    messageBox.setWindowIcon(QIcon(":/img/img.png"));

    //---------------------------------------access rights---------------------------
    tmRights = new QSqlRelationalTableModel(this, db);

    tmRights->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(ui->logPasAction);
    this->addAction(ui->actionEsc);
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

    connect(ui->addRightsAction, SIGNAL(triggered(bool)), this, SLOT(addRights()));
    connect(ui->delRightsAction, SIGNAL(triggered(bool)), this, SLOT(delRights()));
    connect(ui->logPasAction, SIGNAL(triggered(bool)), this, SLOT(logPas()));
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
    if(!tmRights->select()) throw criticalExc("tmRights->select() 1: " + tmRights->lastError().text()); //верно - throw уходит дальше
    setWindowTitle(tr("Права доступа пользователя: ") + uName);
    show();
}

void Rights::sorting(int column, Qt::SortOrder sortOrder)
{
    tmRights->sort(column, sortOrder);
}

void Rights::addRights()
{
    try {
        QSqlQuery testKindsQuery(tmRights->database());
        QSqlQuery typeProductsQuery(tmRights->database());
        QSqlQuery authorityKindsQuery(tmRights->database());
        if (!testKindsQuery.exec("SELECT * FROM tabtestkinds;"))
            throw criticalExc("Select 1r: " + testKindsQuery.lastError().text());
        if (!typeProductsQuery.exec("SELECT * FROM tabtypeproducts;"))
            throw criticalExc("Select 2r: " + typeProductsQuery.lastError().text());
        if (!authorityKindsQuery.exec("SELECT * FROM tabauthoritykinds;"))
            throw criticalExc("Select 3r: " + authorityKindsQuery.lastError().text());
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
        //    qDebug() << idTestKinds.at(rDialog.data.at(2).toInt());
        //    qDebug() << idTypeProducts.at(rDialog.data.at(3).toInt());
        //    qDebug() << idAuthorityKinds.at(rDialog.data.at(4).toInt());

        //    rec.setValue(0, lastKeyAccessRights+1);
        rec.setValue(1, rDialog.lpID);
        rec.setValue(2, idTestKinds.at(rDialog.data.at(2).toInt()));
        rec.setValue(3, idTypeProducts.at(rDialog.data.at(3).toInt()));
        rec.setValue(4, uKey);
        rec.setValue(5, idAuthorityKinds.at(rDialog.data.at(4).toInt()));

        if(!tmRights->insertRecord(-1,rec)) throw criticalExc("Insert 0: tmRights->insertRecord(-1,rec)");
        if(!tmRights->select()) throw criticalExc("tmRights->select() 1: " + tmRights->lastError().text());
        ui->statusbar->showMessage(tr("Добавлено право пользователя"), 10000);
    }
    catch (const criticalExc& exc) {
        messageBox.warning(this, tr("Ошибка при добавлении"), exc);
    }
}

void Rights::logPas()
{
    try {
        QModelIndexList rowsList = ui->tableView->selectionModel()->selectedRows(1);
        if (rowsList.count() == 0) {
            messageBox.warning(this, tr("Логин-пароль"), tr("В таблице нет выделенного поля"));
            return;
        }
        int lpKey = rowsList.at(0).data().toInt();
        //qDebug() << "lpKey:" << lpKey;
        QString numStr = "Строка №" + QString::number(rowsList.at(0).row() + 1);

        QSqlQuery qlp(tmRights->database());
        if(!qlp.exec(QString("SELECT * FROM tabloginpassword WHERE idTabLoginPassword = %1;").arg(QString::number(lpKey))))
            throw criticalExc("Select logPas 1: " + qlp.lastError().text());
        qlp.next();

        lpDialog lpdialog(0, qlp.value(1).toString(), qlp.value(2).toString(), tmRights->database());
        lpdialog.setWindowTitle(numStr);
        lpdialog.lpID = lpKey;
        lpdialog.uID = ui->tableView->selectionModel()->selectedRows(4).at(0).data().toInt();
        lpdialog.rID = ui->tableView->selectionModel()->selectedRows(0).at(0).data().toInt();

        if (lpdialog.exec()) {
            if(!tmRights->select()) throw criticalExc("Select logPas 2: " + tmRights->lastError().text());
            ui->statusbar->showMessage(tr("Изменения завершены успешно"), 10000);
        } else {
            ui->statusbar->showMessage(tr("Отмена изменения логина и пароля"), 10000);
            return;
        }
    }
    catch (const criticalExc& exc) {
        messageBox.warning(this, tr("Ошибка \"логин-пароль\""), exc);
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
        if (QMessageBox::No == messageBox.question(this, tr("Удаление права доступа"), tr("Право доступа будет удалено. Продолжить удаление?"), QMessageBox::Yes, QMessageBox::No)) return;

        int lpID = rowsList.at(0).data().toInt();

        if (!tmRights->removeRow(rowsList.at(0).row())) throw criticalExc("Remove 0: tmRights->removeRow(rowsList.at(0).row())");

        LP lp(0, tmRights->database(), "", "", 0);
        lp.prevLpID = lpID;
        lp.delPrevLP();

        if (!tmRights->select()) throw criticalExc("Select logPas 3: " + tmRights->lastError().text());
        ui->statusbar->showMessage(tr("Право доступа удалено"), 5000);
    }
    catch (const criticalExc& exc) {
        messageBox.warning(this, tr("Ошибка удаления прав"), exc);
    }
}
