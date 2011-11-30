#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "ui_LoginDialog.h"

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QDebug>

class LoginDialog : public QDialog, public Ui::LoginDialog
{
    Q_OBJECT

    public:
        LoginDialog(const QString& defaultUser="", QWidget* parent = 0);
        ~LoginDialog() {qDebug() << "Deleting LoginDialog";};

        QString Name;
        QString Domain;
        QString Passw;

    public slots:
        void scrollUserUp();
        void scrollUserDown();

    private slots:
        void postprocess();
};

#endif // LOGINDIALOG_H

