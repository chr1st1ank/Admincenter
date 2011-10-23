#include "MenuDialog.hpp"

#include "auxiliaries.hpp"
#include "debug.h"
#include "version.h"

#include <QGridLayout>
#include <QLayoutItem>
#include <QPushButton>
#include <QShortcut>
#include <QKeySequence>
#include <QIcon>
#include <QLabel>
#include <QDebug>

MenuDialog::MenuDialog()
    :   QDialog(0,  Qt::WindowFlags(Qt::Dialog | Qt::WindowMinimizeButtonHint)),
        _buttons(),
        _shortcuts(),
        _layout(new QGridLayout)
{
    setWindowIcon(QIcon("icons/admincenter.png"));

    QPushButton* pb = new QPushButton("0", this);
    QShortcut* sc = new QShortcut(QKeySequence('0'), this);
    QObject::connect(sc, SIGNAL(activated()), pb, SLOT(animateClick()));
    _buttons.push_back(pb);
    _shortcuts.push_back(sc);

    for(int i=1; i!=10; ++i)
    {
        pb = new QPushButton(QString::number(i));
        sc = new QShortcut(QKeySequence(digitToChar(i)), this);
        QObject::connect(sc, SIGNAL(activated()), pb, SLOT(animateClick()));
        _buttons.push_back(pb);
        _shortcuts.push_back(sc);
        _layout->addWidget(pb, (9-i)/3, (i+2)%3);
        pb->setDisabled(true);
    }
    _layout->addWidget(_buttons[0], 3, 1);
    QLabel* versionLabel = new QLabel(
        "Version " + QString::fromLocal8Bit(AutoVersion::FULLVERSION_STRING) +
        " - Build " + QString::number(AutoVersion::BUILDS_COUNT),this);
    _layout->addWidget(versionLabel, 4, 0, 1, 2);
    QPushButton* infoButton = new QPushButton("Info", this);
    _layout->addWidget(infoButton, 4, 2, Qt::AlignRight);
//    for(int i=0; i!=3; ++i)
//    {
//        _layout->setRowMinimumHeight(i, 100);
//        _layout->setColumnMinimumWidth(i, 100);
//    }
//    _layout->setRowMinimumHeight(3, 100);
    setLayout(_layout);
    setTitle();
}

MenuDialog::~MenuDialog()
{
    qDebug() << "Deleting MenuDialog";
}

void MenuDialog::setButton(unsigned i, QAbstractButton* pb)
{
    Q_ASSERT(i < 10);
    Q_ASSERT(_buttons.size() == 10);
    Q_ASSERT(_shortcuts.size() == 10);

    unsigned row, col;
    if(i == 0)
    {
        row = 3;
        col = 1;
    }else{
        row = (9-i)/3;
        col = (i+2)%3;
    }
    delete _buttons.at(i);
    _buttons.at(i) = pb;
    pb->setParent(this);
    QObject::connect(_shortcuts.at(i), SIGNAL(activated()), pb, SLOT(animateClick()));
    _layout->addWidget(pb, row, col);
}

void MenuDialog::setTitle(const QString& title)
{
    if(title == "")
        setWindowTitle("Admincenter");
    else
        setWindowTitle("Admincenter - " + title);
}
