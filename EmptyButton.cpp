#include "EmptyButton.hpp"

#include <QSize>

const int emptyButton_x = 135;
const int emptyButton_y = 80;

EmptyButton::EmptyButton(QWidget* parent)
    :   QToolButton(parent)
{
    setMinimumSize(emptyButton_x, emptyButton_y);
    setMaximumSize(emptyButton_x, emptyButton_y);
    setIconSize(QSize(32, 32));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

EmptyButton::EmptyButton(int number, QWidget* parent)
    :   QToolButton(parent)
{
    setText(prepareButtonText(number, ""));
    setMinimumSize(emptyButton_x, emptyButton_y);
    setMaximumSize(emptyButton_x, emptyButton_y);
    setIconSize(QSize(32, 32));
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}


QString EmptyButton::prepareButtonText(int number, const QString& text)
{
    int maxWidth = 20;
    QStringList newTextParts;
//    newTextParts.append("- " + QString::number(number) + " -");

    QStringList parts = text.split(" ", QString::SkipEmptyParts);
    QString current;
    for(QStringList::iterator it=parts.begin(); it!=parts.end(); ++it)
    {
        if(current.size() == 0)
        {
            current = *it;
        }
        else if(current.size() + it->size() + 1 > maxWidth)
        {
            newTextParts.append(current);
            current = *it;
        }
        else
        {
            current += " " + *it;
        }
    }
    newTextParts.append(current);
    return newTextParts.join("\n");
}
