#include "BackButton.hpp"
#include "MenuPresenter.hpp"

#include <QDebug>

BackButton::BackButton(const QIcon& icon, const QString& text, QWidget* parent)
    :   EmptyButton(parent)
{
    setIcon(icon);
    setText(prepareButtonText(0, text));
    connect(this, SIGNAL(clicked()), this, SLOT(execute()));
}

BackButton::~BackButton()
{
    qDebug() << "Deleting BackButton";
}

void BackButton::execute()
{
    MenuPresenter::instance()->stepBack();
}
