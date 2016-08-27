/****************************************************************************
**
** Developer: Igor Alaev
** Contact: alaev@module.ru
** Company: Research Center Module
**
****************************************************************************/

#ifndef RIGHTDIALOG_H
#define RIGHTDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class rightDialog;
}

class rightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit rightDialog(QWidget *parent, QVector<QStringList> &strLists);
    ~rightDialog();

    QStringList data;

public slots:
    void setData(bool);

private:
    Ui::rightDialog *ui;
};

#endif // RIGHTDIALOG_H
