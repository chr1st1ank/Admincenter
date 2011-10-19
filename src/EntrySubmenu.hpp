#ifndef ENTRYSUBMENU_HPP
#define ENTRYSUBMENU_HPP

#include "Entry.hpp"
#include "Menulist.hpp"

#include <string>

class EntrySubmenu : public Entry
{
    public:
        EntrySubmenu(
            const std::string& titel,
            Menulist* liste
        );
        virtual void execute();
        virtual std::string type() const {return "EntrySubmenu";};
        virtual std::string string();
    private:
        Menulist* _menueliste;
};


#endif // ENTRYSUBMENU_HPP

