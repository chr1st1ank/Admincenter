#ifndef ENTRYAPPLICATION_HPP
#define ENTRYAPPLICATION_HPP

#include "Entry.hpp"
#include "Menulist.hpp"

#include <QString>


class EntryApplication : public Entry
{
    public:
        EntryApplication(
            const QString& titel,
            const QString& icon,
            const QString& programmname,
            const QString& parameter,
            const QString& pfad,
            bool unsichtbar = false
        );
        virtual void execute();
        virtual QString type() const {return "EntryApplication";};
//        virtual QString string();
    private:
        QString _programmname;
        QString _parameter;
        QString _pfad;
        bool _unsichtbar;
};


#endif // ENTRYAPPLICATION_HPP

