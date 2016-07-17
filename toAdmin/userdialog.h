#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>

namespace Ui {
class userDialog;
}

class userDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userDialog(QWidget *parent = 0);
    ~userDialog();
    QStringList data;
    int flat;

public slots:
    void setData();

private:
    Ui::userDialog *ui;
};

#endif // USERDIALOG_H
