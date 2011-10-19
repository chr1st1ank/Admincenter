#ifndef EMPTYBUTTON_HPP
#define EMPTYBUTTON_HPP

#include <QPushButton>
#include <QToolButton>


class EmptyButton : public QToolButton
{
    public:
        EmptyButton(QWidget* parent = 0);
        EmptyButton(int number, QWidget* parent = 0);

        static QString prepareButtonText(int number, const QString& text);
};

#endif // EMPTYBUTTON_HPP
