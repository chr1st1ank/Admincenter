#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "ui_LoginDialog.h"

#include <QDialog>
#include <QWidget>

class LoginDialog : public QDialog, public Ui::LoginDialog
{
    Q_OBJECT

    public:
        LoginDialog(const std::string& defaultUser="", QWidget* parent = 0);

        std::string Name;
        std::string Domain;
        std::string Passw;

    public slots:
        void scrollUserUp();
        void scrollUserDown();

    private slots:
        void postprocess();
};

#endif // LOGINDIALOG_H

