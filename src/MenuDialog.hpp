#ifndef MENUDIALOG_HPP
#define MENUDIALOG_HPP

#include "Menulist.hpp"

//#include <QDialog>
#include <QMainWindow>

class QAbstractButton;
class QShortcut;
class QGridLayout;

class MenuDialog : public QMainWindow//QDialog
{
    Q_OBJECT

    public:
        MenuDialog();
//        MenuDialog(Menulist* ml);
        ~MenuDialog();
        void setButton(unsigned i, QAbstractButton* pb);
        void setTitle(const QString& title="");
        void quit();

    public slots:
        void editConfig();
        void reload();
        void showInfo();

    private:
        std::vector<QAbstractButton*> _buttons;
        std::vector<QShortcut*> _shortcuts;
        QGridLayout* _layout;
};

#endif // MENUDIALOG_HPP
