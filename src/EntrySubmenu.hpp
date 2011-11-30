#ifndef ENTRYSUBMENU_HPP
#define ENTRYSUBMENU_HPP

#include "Entry.hpp"
#include "Menulist.hpp"

#include <QString>
#include <QDebug>

class EntrySubmenu : public Entry
{
    public:
        EntrySubmenu(
            const QString& titel,
            Menulist* liste
        );
        ~EntrySubmenu() {qDebug() << "Deleting EntrySubmenu";};
        virtual void execute();
        virtual QString type() const {return "EntrySubmenu";};
//        virtual QString string();
    private:
        Menulist* _menueliste;
};


#endif // ENTRYSUBMENU_HPP

