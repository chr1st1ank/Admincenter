#ifndef SETTINGSPARSER_HPP_INCLUDED
#define SETTINGSPARSER_HPP_INCLUDED

#include "Menulist.hpp"

#include "xmlsp/xmlsp.h"
#include <string>
#include <stack>

class SettingsParser: public XMLSP::Parser
{
public:
    virtual ~SettingsParser() {};

    virtual bool on_tag_open(std::string tag_name, XMLSP::StringMap& attributes);
    virtual bool on_cdata(std::string cdata);
    virtual bool on_tag_close(std::string tag_name);
    virtual bool on_comment(std::string comment);
    virtual bool on_processing(std::string value);
    virtual bool on_doctype(std::string value);
    virtual bool on_document_begin();
    virtual bool on_document_end();
    virtual void on_error(int errno, int line, int col, std::string message);

    Menulist* get_liste();
    std::string get_user();

private:
    std::stack<Menulist*> listenstack;
    std::string _user;
};

#endif // SETTINGSPARSER_HPP_INCLUDED
