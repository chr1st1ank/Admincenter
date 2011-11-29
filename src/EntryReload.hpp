#ifndef ENTRYRELOAD_HPP
#define ENTRYRELOAD_HPP

#include "Entry.hpp"
#include "Menulist.hpp"

#include <QString>


class EntryReload : public Entry
{
    public:
        EntryReload(
            const QString& titel,
            const QString& icon
        );
        virtual void execute();
        virtual QString type() const {return "EntryReload";};
//        virtual QString string();
};

#endif // ENTRYRELOAD_HPP
