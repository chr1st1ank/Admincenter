
#include "Menulist.hpp"
#include "Entry.hpp"
#include "auxiliaries.hpp"
#include "debug.h"
//#include <string>
#include <vector>
#include <stack>
#include <stdexcept>
#include <sstream>

#include <iostream>

Menulist::Menulist(const QString& titel)
    : _titel(titel), _eintragliste()
{}
//Menulist::Menulist(std::vector<Entry> liste) : _eintragliste(liste)
//{}
QString Menulist::titel()
{
    return _titel;
}
std::vector<QString> Menulist::titelliste()
{
    std::vector<QString> v;
    for(std::vector<Entry*>::iterator i = _eintragliste.begin();
        i != _eintragliste.end(); ++i)
    {
        v.push_back((*i)->titel());
    }
    return v;
}
unsigned int Menulist::get_menuelaenge() const
{
    return _eintragliste.size();
}
Entry* Menulist::get_menueeintrag(unsigned int i) const
{
    cASSERTX(i<=_eintragliste.size(), "Wrong index in Menulist::get_menueeintrag(i)");
    return _eintragliste.at(i);
}
void Menulist::add_menueeintrag(Entry* eintrag)
{
    _eintragliste.push_back(eintrag);
}
void Menulist::add_menueeintrag(unsigned int position, Entry* eintrag)
{
    _eintragliste.insert(_eintragliste.begin()+position, eintrag);
}
void Menulist::del_menueeintrag(unsigned int position)
{
    _eintragliste.erase(_eintragliste.begin()+position);
}
//QString Menulist::string()
//{
//    std::ostringstream ss;
//    for(std::vector<Entry*>::const_iterator i = _eintragliste.begin();
//        i != _eintragliste.end(); ++i)
//    {
//        ss << (*i)->string() << "\n";
//    }
//    return ss.str();
//}
//QString Menulist::toXML()
//{
//    std::ostringstream ss;
//    ss << "<Hauptmenue>\n";
//    for(std::vector<Entry*>::const_iterator i = _eintragliste.begin();
//        i != _eintragliste.end(); ++i)
//    {
//        ss << (*i)->string() << "\n";
//    }
//    ss << "</Hauptmenue>";
//    return ss.str();
//}
//Menulist* Menulist::fromXML(const std::string& xml)
//{
//	SettingsParser p;
//	p.set_skip_whitespaces(true);
//	std::cout << "parsing|" << xml << "|docend"<< std::endl;
////	exit(-9);
//    if(p.parse(xml)){
//	    exit(-9);
//		return p.get_liste();
//	} else {
//		std::cout<<"Aborted."<<std::endl;
//		return 0;
//	}
//}
