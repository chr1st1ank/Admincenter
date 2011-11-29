#ifndef RELOADBUTTON_HPP
#define RELOADBUTTON_HPP

#include "EmptyButton.hpp"

class ReloadButton : public EmptyButton
{
    Q_OBJECT

    public:
        ReloadButton(int number, const QIcon& icon, const QString& text, QWidget* parent = 0);

    public slots:
        void execute();
};

#endif // RELOADBUTTON_HPP
