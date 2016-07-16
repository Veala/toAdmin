#include "admin.h"
#include <QApplication>

#define debug_1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef debug_1
     QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
     db.setDatabaseName("BDBIVKM");
     db.setHostName("localhost");
     db.setPort(3306);
     db.setUserName("root");
     db.setPassword("MySql123");
    if (! db.open()) {
        //QMessageBox::warning(this, tr("Невозможно открыть базу данных"), tr("Ошибка: ") +  db.lastError().text());
        return 1;
    }
#endif

    Admin w(0, db);
    w.show();

    return a.exec();
}
