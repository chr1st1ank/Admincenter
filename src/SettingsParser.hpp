#ifndef SETTINGSPARSER_HPP_INCLUDED
#define SETTINGSPARSER_HPP_INCLUDED

#include "Menulist.hpp"

#include "xmlsp/xmlsp.h"
#include <QString>
#include <QDebug>
#include <string>
#include <stack>

class SettingsParser: public XMLSP::Parser
{
public:
    virtual ~SettingsParser() {qDebug() << "Deleting SettingsParser";};

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
    QString get_user();
    QString get_textEditor();

private:
    std::stack<Menulist*> listenstack;
    QString _user;
    QString _textEditor;
};

#endif // SETTINGSPARSER_HPP_INCLUDED
