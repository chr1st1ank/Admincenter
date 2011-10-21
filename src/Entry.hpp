#ifndef ENTRY_HPP
#define ENTRY_HPP

//#include <string>

class Entry
{
    public:
        virtual ~Entry() {};

        virtual void execute(){};
        virtual std::string type() const {return "Entry";};
        virtual std::string titel(){return _titel;};
        virtual std::string icon(){return _icon;};
        virtual std::string string(){return "";};
    protected:
        std::string _titel;
        std::string _icon;
};

#endif // ENTRY_HPP


