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
        enum exitStatus{ exitStatusSuccess, exitStatusRestart, exitStatusFailed };

        static MenuPresenter* instance();
        void updateList(Menulist* ml);
        void showDialog();
        void stepBack();
        void MenuPresenter::quit();
        void announceReload();
        exitStatus status() { return _exitStatus; };
    private:
        exitStatus _exitStatus;
        MenuDialog* _menuDialog;
        std::stack<Menulist*> _lists;
};

#endif // MENUPRESENTER_HPP
