#ifndef RIGHTS_H
#define RIGHTS_H

#include <QMainWindow>
#include <QtSql>
#include <QTableView>
#include <QMessageBox>

namespace Ui {
class Rights;
}

class Rights : public QMainWindow
{
    Q_OBJECT

public:
    explicit Rights(QWidget *parent, QSqlDatabase &db);
    ~Rights();

    QSqlRelationalTableModel *tmRights;
    QSqlTableModel *tmLogPas;
    QTableView *lpView;

public slots:
    void init(int uKey, QString uNmae);
    void sorting(int,Qt::SortOrder);
    void addRights();
    void logPas();
    void delRights();

private:
    Ui::Rights *ui;
};

#endif // RIGHTS_H
