#ifndef MENUPRESENTER_HPP
#define MENUPRESENTER_HPP

#include "MenuDialog.hpp"

#include "Menulist.hpp"

#include <stack>

class MenuPresenter
{
    private:
        MenuPresenter();
        MenuPresenter(const MenuPresenter& other);
        ~MenuPresenter();

    public:
        static MenuPresenter* instance();

        /// Clear the stack of opened menus and refresh the dialog with a new list
        void setList(Menulist* ml);

        /// Push a new Menulist onto the stack of opened menus and show it
        void pushList(Menulist* ml);

        void showDialog();
        void stepBack();
        void quit();
    private:
        MenuDialog* _menuDialog;
        std::stack<Menulist*> _lists;
};

#endif // MENUPRESENTER_HPP
