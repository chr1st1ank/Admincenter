#include "MenuPresenter.hpp"
#include "MenuButton.hpp"
#include "BackButton.hpp"
#include "EmptyButton.hpp"

#include "Entry.hpp"
//#include "menueeintraege.hpp"
#include "debug.h"

#include <QDebug>
#include <QString>
#include <QStringList>

MenuPresenter::MenuPresenter()
    :   _menuDialog(new MenuDialog()),
        _lists()
{
}

MenuPresenter::~MenuPresenter()
{
    delete _menuDialog;
}

MenuPresenter* MenuPresenter::instance()
{
    static MenuPresenter _instance;
    return &_instance;
}

void MenuPresenter::updateList(Menulist* ml)
{
    Q_ASSERT(ml);

    // Ensure there are not too many entries.
    unsigned len = ml->get_menuelaenge();
    if(len > 9)
    {
        qDebug() << "Warning: Cut an overlong menu with size of " << ml->get_menuelaenge() << " to the size of 9";
        len = 9;
    }

    // Create Menu Buttons
    for(unsigned i=0; i!=len; ++i)
    {
        Entry* me = ml->get_menueeintrag(i);
        MenuButton* pb = new MenuButton(me, i+1);
        _menuDialog->setButton(i+1, pb);
    }

    // Fill with inactive empty buttons
    for(unsigned i=len; i!=9; ++i)
    {
        EmptyButton* eb = new EmptyButton(i+1);
        _menuDialog->setButton(i+1, eb);
        eb->setDisabled(true);
    }

    // Create the back/exit button
    QAbstractButton* backbutton;
    if(_lists.empty())
    {
        backbutton = new BackButton(QIcon(QString("icons/quit.png")), QString(QString::fromUtf8("Beenden")));
    }else{
        backbutton = new BackButton(QIcon(QString("icons/back.png")), QString(QString::fromUtf8("Zurück")));
    }
    _menuDialog->setButton(0, backbutton);

    // Track the menu list for the go-back function
    _lists.push(ml);

    // Change the window title
    _menuDialog->setTitle(QString::fromLocal8Bit(ml->titel().c_str()));
}

void MenuPresenter::showDialog()
{
    _menuDialog->show();
}

void MenuPresenter::stepBack()
{
    Q_ASSERT(!_lists.empty());
    _lists.pop();
    if(_lists.empty())
    {
        _menuDialog->accept();
    }else{
        Menulist* ml = _lists.top();
        _lists.pop();
        updateList(ml);
    }
}
