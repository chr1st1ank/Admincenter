#include "MenuButton.hpp"
#include "MenuPresenter.hpp"

#include <QDebug>
#include <QString>
#include <QIcon>

MenuButton::MenuButton(Entry* menueeintrag, int number, QWidget* parent)
    :   EmptyButton(parent),
        _menueeintrag(menueeintrag)
{
    setText(prepareButtonText(number, menueeintrag->titel()));
    QString icon = menueeintrag->icon();
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
    qDebug() << "Deleting MenuButton";
}

void MenuButton::execute()
{
    _menueeintrag->execute();
}
