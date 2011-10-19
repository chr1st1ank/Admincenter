
#include "LoginDialog.hpp"
#include "OperatingSystem.hpp"
#include "debug.h"

#include <QShortcut>
#include <QPushButton>
#include <QIcon>
#include <QSize>

LoginDialog::LoginDialog(const std::string& defaultUser, QWidget* parent) : QDialog(parent)
{
    setupUi(this);

    setWindowIcon(QIcon("icons/admincenter.png"));

    // Setup the button icons
    QPushButton* pb = buttonBox->button(QDialogButtonBox::Ok);
    Q_ASSERT(pb);
    pb->setIcon(QIcon("icons/ok.png"));
    pb = buttonBox->button(QDialogButtonBox::Close);
    Q_ASSERT(pb);
    pb->setIcon(QIcon("icons/quit.png"));

    // Setup the user list and its shortcuts
    QShortcut* sc;
    sc = new QShortcut(Qt::Key_Up, this);
    QObject::connect(sc, SIGNAL(activated()), this, SLOT(scrollUserUp()));
    sc = new QShortcut(QKeySequence('8'), this);
    QObject::connect(sc, SIGNAL(activated()), this, SLOT(scrollUserUp()));
    sc = new QShortcut(Qt::Key_Down, this);
    QObject::connect(sc, SIGNAL(activated()), this, SLOT(scrollUserDown()));
    sc = new QShortcut(QKeySequence('2'), this);
    QObject::connect(sc, SIGNAL(activated()), this, SLOT(scrollUserDown()));

    // Fill the user list and activate the default user
    int activeRow = 0;
    QString qdefaultUser = QString::fromLocal8Bit(defaultUser.c_str()).toLower();
    std::vector<std::string> konten = OperatingSystem::lokale_benutzer();
    for(std::vector<std::string>::const_iterator it=konten.begin(); it!=konten.end(); ++it)
    {
        QString user = QString::fromLocal8Bit(it->c_str());
        if(user.toLower() == qdefaultUser)
            activeRow = it - konten.begin();
        userList->addItem(user);
    }
    userList->setCurrentRow(activeRow);
    pwEdit->setFocus(Qt::ShortcutFocusReason);

    //TODO: This is just for testing
    cDEBUG("Appdir: " + OperatingSystem::get_appdir());
    cDEBUG("get_appname: " + OperatingSystem::get_appname());
    cDEBUG("get_cd: " + OperatingSystem::get_cd());

    // Store the active user and domain as default values
    OperatingSystem::get_user(Name, Domain);

    // Finishing event
    connect(this, SIGNAL(accepted()), this, SLOT(postprocess()));
}

void LoginDialog::scrollUserUp()
{
    int row = userList->currentRow();
    if(row > 0)
        --row;
    userList->setCurrentRow(row);
    pwEdit->setFocus(Qt::ShortcutFocusReason);
}

void LoginDialog::scrollUserDown()
{
    int row = userList->currentRow();
    if(row + 1 < userList->count())
        ++row;
    userList->setCurrentRow(row);
    pwEdit->setFocus(Qt::ShortcutFocusReason);
}

void LoginDialog::postprocess()
{
    Name = userList->currentItem()->text().toStdString();
    Passw = pwEdit->text().toStdString();
}
