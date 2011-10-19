#include "BackButton.hpp"
#include "MenuPresenter.hpp"

BackButton::BackButton(const QIcon& icon, const QString& text, QWidget* parent)
    :   EmptyButton(parent)
{
    setIcon(icon);
    setText(prepareButtonText(0, text));
    connect(this, SIGNAL(clicked()), this, SLOT(execute()));
}

void BackButton::execute()
{
    MenuPresenter::instance()->stepBack();
}
