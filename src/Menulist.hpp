#ifndef MENULIST_HPP
#define MENULIST_HPP

#include "Entry.hpp"

#include <vector>
#include <QDebug>

//typedef Entry::Entry me;
typedef Entry me;
class Menulist
{
    public:
        Menulist(const QString& _titel);
//        Menulist(const std::string& _titel, std::vector<Entry> liste);
        ~Menulist() {qDebug() << "Deleting Menulist";};

        QString titel();
        std::vector<QString> titelliste();

        unsigned int get_menuelaenge() const;
        me* get_menueeintrag(unsigned int i) const;
        void add_menueeintrag(me* eintrag);
        void add_menueeintrag(unsigned int position, me* eintrag);
        void del_menueeintrag(unsigned int position);

//        QString toXML();
//        QString string();

//        static Menulist* fromXML(const std::string& xml);

//        ///Menue laden und speichern
//        bool laden();
//        bool speichern();
//        std::string get_dateiname() const;
//        void set_dateiname(const std::string& datei);
//
//        ///Menüeinträge im Wartungsmenü bearbeiten
//        unsigned int get_menuelaenge() const;
//        menueeintrag get_menueeintrag(int i) const;
//        void add_menueeintrag(const std::string& titel
//                                     ,const std::string& programmname
//                                     ,const std::string& parameter = ""
//                                     ,const std::string& pfad = ""
//                                     ,bool unsichtbar = false);
//        void add_menueeintrag(unsigned int position
//                                     ,const std::string& titel
//                                     ,const std::string& programmname
//                                     ,const std::string& parameter = ""
//                                     ,const std::string& pfad = ""
//                                     ,bool unsichtbar = false);
//        void del_menueeintrag(int position);
//        //Funktion, um einen Eintrag zu modifizieren

    private:
        QString _titel;
        std::vector<me*> _eintragliste;
};

#endif // MENULIST_HPP

