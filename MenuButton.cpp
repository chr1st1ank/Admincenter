#include "MenuButton.hpp"
#include "MenuPresenter.hpp"

#include <QDebug>
#include <QString>
#include <QIcon>

MenuButton::MenuButton(Entry* menueeintrag, int number, QWidget* parent)
    :   EmptyButton(parent),
        _menueeintrag(menueeintrag)
{
    setText(prepareButtonText(number, QString::fromLocal8Bit(menueeintrag->titel().c_str())));
    QString icon = QString::fromLocal8Bit(menueeintrag->icon().c_str());
    if(icon == "")
    {
        if(menueeintrag->type() == "EntrySubmenu")
            icon = "icons/submenu.png";
        else if(menueeintrag->type() == "EntryApplication")
            icon = "icons/exec.png";
    }
    setIcon(QIcon(icon));
    connect(this, SIGNAL(clicked()), this, SLOT(execute()));
}

MenuButton::~MenuButton()
{
}

void MenuButton::execute()
{
    _menueeintrag->execute();
}
