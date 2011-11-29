
#include "SettingsParser.hpp"
#include "Entry.hpp"
#include "EntrySubmenu.hpp"
#include "EntryApplication.hpp"
#include "EntryReload.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <QString>

#include "debug.h"

#define pDEBUG(s)

bool SettingsParser::on_tag_open(std::string tag_name, XMLSP::StringMap& attributes)
{
    pDEBUG("on_tag_open:" << tag_name);
    if (tag_name == "Benutzer")
    {
        for (XMLSP::StringMap::const_iterator i = attributes.begin();
                i != attributes.end(); i++)
        {
            if (i->first == "name") _user = QString::fromLocal8Bit(i->second.c_str(),i->second.size());
            break;
        }
    }
    else if (listenstack.empty())
    {
        if (tag_name != "Hauptmenue")
            throw std::invalid_argument("Hauptmenue als Toplevel-Tag erwartet");
        listenstack.push(new Menulist("Hauptmenue"));
    }
    else if (tag_name == "Untermenue")
    {
        QString titel = "";
        for (XMLSP::StringMap::const_iterator i = attributes.begin();
                i != attributes.end(); i++)
        {
            if (i->first == "titel")
                titel = QString::fromLocal8Bit(i->second.c_str());
        }
        listenstack.push(new Menulist(titel));
    }
    else if (tag_name == "Reload")
    {
        QString titel = "";
        QString icon = "";
        for (XMLSP::StringMap::const_iterator i = attributes.begin();
                i != attributes.end(); i++)
        {
            if (i->first == "titel"){
                titel = QString::fromLocal8Bit(i->second.c_str());
            }else if (i->first == "icon"){
                icon = QString::fromLocal8Bit(i->second.c_str());
            }
        }
        listenstack.top()->add_menueeintrag(new EntryReload(
                                                titel, icon
                                            ));
    }
//    else if (listenstack.empty())
//    {
//        throw std::logic_error("Komischer Fehler im xml-parser!");
//    }
    else if (tag_name == "Programm")
    {
        QString titel = "";
        QString programmname = "";
        QString parameter = "";
        QString pfad = "";
        bool unsichtbar = false;
        QString icon = "";
        for (XMLSP::StringMap::const_iterator i = attributes.begin();
                i != attributes.end(); i++)
        {
            if (i->first == "titel"){
                titel = QString::fromLocal8Bit(i->second.c_str());
            }else if (i->first == "icon"){
                icon = QString::fromLocal8Bit(i->second.c_str());
            }else if (i->first == "programmname"){
                programmname = QString::fromLocal8Bit(i->second.c_str());
            }else if (i->first == "parameter"){
                parameter = QString::fromLocal8Bit(i->second.c_str());
            }else if (i->first == "pfad"){
                pfad = QString::fromLocal8Bit(i->second.c_str());
            }else if (i->first == "unsichtbar" && (i->second=="true"||i->second=="1")){
                unsichtbar = true;
            }
        }
        listenstack.top()->add_menueeintrag(new EntryApplication(
                                                titel, icon, programmname, parameter, pfad, unsichtbar
                                            ));
    }
//    else if (tag_name == "Plugin")
//    {
//        std::string titel = "";
//        std::string icon = "";
//        for (XMLSP::StringMap::const_iterator i = attributes.begin();
//                i != attributes.end(); i++)
//        {
//            if (i->first == "titel"){
//                titel = i->second;
//            }else if (i->first == "icon"){
//                icon = i->second;
//            }else if (i->first == "programmname"){
//                programmname = i->second;
//            }else if (i->first == "parameter"){
//                parameter = i->second;
//            }else if (i->first == "pfad"){
//                pfad = i->second;
//            }else if (i->first == "unsichtbar" && (i->second=="true"||i->second=="1")){
//                unsichtbar = true;
//            }
//        }
//        listenstack.top()->add_menueeintrag(new EntryApplication(
//                                                titel, icon, programmname, parameter, pfad, unsichtbar
//                                            ));
//    }
    else
    {
        throw std::invalid_argument("Unbekannter tag "+tag_name);
    }
    return true;
}

bool SettingsParser::on_cdata(std::string cdata)
{
    pDEBUG("on_cdata:" << cdata);
    cdata.clear();//TODO: Only to supress "unused parameter"-warning
    return true;
}

bool SettingsParser::on_tag_close(std::string tag_name)
{
    pDEBUG("on_tag_close:" << tag_name);
    if (tag_name == "Untermenue" && listenstack.empty())
    {
        throw std::logic_error("Warum ist der Stack leer?");
    }
    else if (tag_name == "Untermenue")
    {
        Menulist* m = listenstack.top();
        listenstack.pop();
        listenstack.top()->add_menueeintrag(new EntrySubmenu(
                                                m->titel(), m
                                            ));
    }
    return true;
}

bool SettingsParser::on_comment(std::string comment)
{
    pDEBUG("on_comment:" << comment);
    return true;
}

bool SettingsParser::on_processing(std::string value)
{
    pDEBUG("on_processing:" << value);
    return true;
}

bool SettingsParser::on_doctype(std::string value)
{
    pDEBUG("on_doctype:" << value);
    return true;
}

bool SettingsParser::on_document_begin()
{
    pDEBUG("starting");
    listenstack = std::stack<Menulist*>();//.clear();
    return true;
}

bool SettingsParser::on_document_end()
{
    pDEBUG("on_document_end");
    return !listenstack.empty();
    return true;
}

void SettingsParser::on_error(int errno, int line, int col, std::string message)
{
    std::ostringstream ss;
    ss << "Fehler beim lesen der Einstellungen. Zeile " << line
    << ", Spalte "<< col <<": " << message <<std::endl;
    std::cerr << ss.str() << std::endl;
    throw std::invalid_argument(ss.str());
}

Menulist* SettingsParser::get_liste()
{
    if (listenstack.empty())
        throw std::out_of_range("Es konnte keine Menulist erzeugt werden.");
    return listenstack.top();
}

QString SettingsParser::get_user()
{
    return _user;
}

