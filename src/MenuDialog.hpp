#ifndef MENUDIALOG_HPP
#define MENUDIALOG_HPP

#include "Menulist.hpp"

#include <QDialog>

class QAbstractButton;
class QShortcut;
class QGridLayout;

class MenuDialog : public QDialog
{
    public:
        MenuDialog();
//        MenuDialog(Menulist* ml);
        ~MenuDialog();
        void setButton(unsigned i, QAbstractButton* pb);
        void setTitle(const QString& title="");

    private:
        std::vector<QAbstractButton*> _buttons;
        std::vector<QShortcut*> _shortcuts;
        QGridLayout* _layout;
};

#endif // MENUDIALOG_HPP
