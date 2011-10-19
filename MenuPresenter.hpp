#ifndef MENUPRESENTER_HPP
#define MENUPRESENTER_HPP

#include "MenuDialog.hpp"

#include "Menulist.hpp"

#include <stack>
#include <QString>

class MenuPresenter
{
    private:
        MenuPresenter();
        MenuPresenter(const MenuPresenter& other);
        ~MenuPresenter();

    public:
        static MenuPresenter* instance();
        void updateList(Menulist* ml);
        void showDialog();
        void stepBack();

    private:
        MenuDialog* _menuDialog;
        std::stack<Menulist*> _lists;
};

#endif // MENUPRESENTER_HPP
