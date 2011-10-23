#ifndef ENTRYSUBMENU_HPP
#define ENTRYSUBMENU_HPP

#include "Entry.hpp"
#include "Menulist.hpp"

#include <QString>

class EntrySubmenu : public Entry
{
    public:
        EntrySubmenu(
            const QString& titel,
            Menulist* liste
        );
        virtual void execute();
        virtual QString type() const {return "EntrySubmenu";};
//        virtual QString string();
    private:
        Menulist* _menueliste;
};


#endif // ENTRYSUBMENU_HPP

