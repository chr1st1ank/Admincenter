
#include "Settings.hpp"
#include "SettingsParser.hpp"
#include "OperatingSystem.hpp"

#include <fstream>

//const std::string Settings::dateiname = OperatingSystem::get_appdir() + "/settings.xml";
const std::string Settings::dateiname = "settings.xml";//Problematisch?


Settings::Settings(std::string filename)
{
    // Datei einlesen
    std::ifstream inFile(filename.c_str(), std::ios::in);
    if (!inFile)
    {
        throw(FileIOError(std::string("Unable to read from settings file")+filename));
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
    parseSettings(xml);
}

void Settings::save(const std::string& filename)
{
    // xml erzeugen
    std::string xml = \
                      "<?xml version=\"1.0\"?>\n"
                      "<!-- \n"
                      "    Erlaubte Tags:\n"
                      "<Programm titel=\"Konsole\" programmname=\"cmd.exe\" parameter=\"\" pfad=\"\" unsichtbar=\"false\" />\n"
                      "<Untermenue titel=\"Wartungsprogramme\" />\n"
                      "<Benutzer name=\"Master\"/>\n"
                      "\n"
                      "XMLSP supports 1 byte entities in decimal and hex forms:\n"
                      "	&#145;\n"
                      "	&xb0;\n"
                      "By default, the parser supports the following entities: &lt; &gt; &amp; &apos;\n"
                      "&quot;. You may add more entites using Parser::add_entity(name, value):\n"
                      "	parser.add_entity(\"nbsp\", 160);\n"
                      "-->\n"
                      "\n";
    xml += _hauptmenue->toXML();
    xml += "\n\n<Benutzer name=\""+_user+"\"/>\n\n";

    // Datei schreiben
    std::ofstream outFile(filename.c_str(), std::ios::out);
    if (!outFile)
    {
        throw(FileIOError(std::string("Unable to write to settings file")));
    }
    outFile.write(xml.c_str(),xml.size());
    outFile.close();
}

Menulist* Settings::hauptmenue()
{
    return _hauptmenue;
}

const std::string& Settings::user()
{
    return _user;
}

void Settings::parseSettings(const std::string& xml)
{
    SettingsParser p;
    p.set_skip_whitespaces(false);
    if (p.parse(xml))
    {
        _hauptmenue = p.get_liste();
        _user = p.get_user();
    }
    else
    {
        throw FileIOError("Error reading file.");
    }
}
