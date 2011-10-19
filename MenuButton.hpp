#ifndef MENUBUTTON_HPP
#define MENUBUTTON_HPP

#include "EmptyButton.hpp"

#include "Entry.hpp"

class MenuButton : public EmptyButton
{
    Q_OBJECT

    public:
        MenuButton(Entry* menueeintrag, int number, QWidget* parent = 0);
        ~MenuButton();

    public slots:
        void execute();

    private:
        Entry* _menueeintrag;
};

#endif // MENUBUTTON_HPP
