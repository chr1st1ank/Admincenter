
#include "Entry.hpp"
#include "EntryApplication.hpp"
#include "OperatingSystem.hpp"
#include "auxiliaries.hpp"

//#include <string>
#include <sstream>
#include <vector>
#include <QString>

using std::vector;
using namespace std;

/************************************************
* EntryApplication
************************************************/
EntryApplication::EntryApplication(
    const QString& titel,
    const QString& icon,
    const QString& programmname,
    const QString& parameter,
    const QString& pfad,
    bool unsichtbar
) : _programmname(programmname),
    _parameter(parameter),
    _pfad(pfad),
    _unsichtbar(unsichtbar)
{
    _titel = titel;
    _icon = icon;
}
void EntryApplication::execute()
{
    OperatingSystem::programm_starten(_programmname,_parameter,_pfad,_unsichtbar);
}
//QString EntryApplication::string()
//{
//    ostringstream ss;
//    ss << "<Programm ";
//    ss << "titel=\"" << xmlescape(_titel) << "\" ";
//    ss << "programmname=\"" << xmlescape(_programmname) << "\" ";
//    ss << "parameter=\"" << xmlescape(_parameter) << "\" ";
//    ss << "pfad=\"" << xmlescape(_pfad) << "\" ";
//    ss << "unsichtbar=\"" << _unsichtbar << "\" ";
//    ss << "/>";
//    return ss.str();
//}


