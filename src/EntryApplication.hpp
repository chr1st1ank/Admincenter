#ifndef ENTRYAPPLICATION_HPP
#define ENTRYAPPLICATION_HPP

#include "Entry.hpp"
#include "Menulist.hpp"

//#include <string>


class EntryApplication : public Entry
{
    public:
        EntryApplication(
            const std::string& titel,
            const std::string& icon,
            const std::string& programmname,
            const std::string& parameter,
            const std::string& pfad,
            bool unsichtbar = false
        );
        virtual void execute();
        virtual std::string type() const {return "EntryApplication";};
        virtual std::string string();
    private:
        std::string _programmname;
        std::string _parameter;
        std::string _pfad;
        bool _unsichtbar;
};


#endif // ENTRYAPPLICATION_HPP

