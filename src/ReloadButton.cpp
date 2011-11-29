#include "ReloadButton.hpp"
#include "MenuPresenter.hpp"

ReloadButton::ReloadButton(int number, const QIcon& icon, const QString& text, QWidget* parent)
    :   EmptyButton(parent)
{
    setIcon(icon);
    setText("test");//prepareButtonText(number, text));
    connect(this, SIGNAL(clicked()), this, SLOT(execute()));
}

void ReloadButton::execute()
{
    MenuPresenter::instance()->announceReload();
    MenuPresenter::instance()->quit();
}

