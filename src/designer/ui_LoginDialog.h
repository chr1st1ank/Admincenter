/********************************************************************************
** Form generated from reading ui file 'LoginDialog.ui'
**
** Created: Tue 29. Nov 17:06:30 2011
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label;
    QListWidget *userList;
    QLabel *label_2;
    QLineEdit *pwEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(191, 300);
        verticalLayout = new QVBoxLayout(LoginDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setWordWrap(true);

        verticalLayout->addWidget(label_3);

        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        userList = new QListWidget(LoginDialog);
        userList->setObjectName(QString::fromUtf8("userList"));

        verticalLayout->addWidget(userList);

        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        pwEdit = new QLineEdit(LoginDialog);
        pwEdit->setObjectName(QString::fromUtf8("pwEdit"));
        pwEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(pwEdit);

        buttonBox = new QDialogButtonBox(LoginDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Close|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(LoginDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LoginDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LoginDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "AdminCenter - Anmeldung", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("LoginDialog", "Bitte w\303\244hlen Sie einen Benutzer aus und geben Sie das zugeh\303\266rige Passwort ein.", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LoginDialog", "Benutzer:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LoginDialog", "Passwort:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(LoginDialog);
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
