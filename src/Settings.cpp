
#include "Settings.hpp"
#include "SettingsParser.hpp"
#include "OperatingSystem.hpp"
#include "debug.h"

#include <fstream>
#include <QDir>

Settings::Settings(QString filename)
{
    cDEBUG("reading settings");
    // Datei einlesen
    std::ifstream inFile(filename.toLocal8Bit().constData(), std::ios::in);
    if (!inFile)
    {
        throw(FileIOError(QString("Unable to read from settings file ")+filename));
    }
    std::string xml = "";
    char c[128];
    do
    {
        inFile.read(c,128);
        xml += std::string(c).substr(0,inFile.gcount());
    }
    while (inFile);
    inFile.close();
    try{
        parseSettings(xml);
    }catch(const std::exception& ex){
        throw(FileIOError(QString("Failed to parse settings file '")+filename+"'. "+ex.what()));
    }
}

//void Settings::save(const QString& filename)
//{
//    // xml erzeugen
//    std::string xml = \
//                      "<?xml version=\"1.0\"?>\n"
//                      "<!-- \n"
//                      "    Erlaubte Tags:\n"
//                      "<Programm titel=\"Konsole\" programmname=\"cmd.exe\" parameter=\"\" pfad=\"\" unsichtbar=\"false\" />\n"
//                      "<Untermenue titel=\"Wartungsprogramme\" />\n"
//                      "<Benutzer name=\"Master\"/>\n"
//                      "\n"
//                      "XMLSP supports 1 byte entities in decimal and hex forms:\n"
//                      "	&#145;\n"
//                      "	&xb0;\n"
//                      "By default, the parser supports the following entities: &lt; &gt; &amp; &apos;\n"
//                      "&quot;. You may add more entites using Parser::add_entity(name, value):\n"
//                      "	parser.add_entity(\"nbsp\", 160);\n"
//                      "-->\n"
//                      "\n";
//    xml += _hauptmenue->toXML();
//    xml += "\n\n<Benutzer name=\""+_user+"\"/>\n\n";
//
//    // Datei schreiben
//    std::ofstream outFile(filename.local8Bit().constData(), std::ios::out);
//    if (!outFile)
//    {
//        throw(FileIOError(std::string("Unable to write to settings file")));
//    }
//    outFile.write(xml.c_str(),xml.size());
//    outFile.close();
//}

Menulist* Settings::hauptmenue()
{
    return _hauptmenue;
}

const QString& Settings::user() const
{
    return _user;
}

const QString& Settings::textEditor() const
{
    return _textEditor;
}

void Settings::parseSettings(const std::string& xml)
{
    SettingsParser p;
    p.set_skip_whitespaces(false);
    if (p.parse(xml))
    {
        _hauptmenue = p.get_liste();
        _user = p.get_user();
        _textEditor = p.get_textEditor();
        cDEBUG("Texteditor: " << _textEditor.toLocal8Bit().constData());
        if(_textEditor.isEmpty())
            _textEditor = QString("C:\\WINDOWS\\NOTEPAD.EXE");
        cDEBUG("Texteditor: " << _textEditor.toLocal8Bit().constData());
    }
    else
    {
        cDEBUG("SettingsParser::parse() returned false");
        throw FileIOError("Error reading file.");
    }
}
