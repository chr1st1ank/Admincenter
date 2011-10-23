#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <QString>

class Entry
{
    public:
        virtual ~Entry() {};

        virtual void execute(){};
        virtual QString type() const {return "Entry";};
        virtual QString titel(){return _titel;};
        virtual QString icon(){return _icon;};
//        virtual QString string(){return "";};
    protected:
        QString _titel;
        QString _icon;
};

#endif // ENTRY_HPP


