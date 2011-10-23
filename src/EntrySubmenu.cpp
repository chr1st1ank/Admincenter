
#include "EntrySubmenu.hpp"
#include "MenuPresenter.hpp"
#include "auxiliaries.hpp"

#include <string>
#include <sstream>

using namespace std;

/************************************************
* EntrySubmenu
************************************************/
EntrySubmenu::EntrySubmenu(
    const QString& titel,
    Menulist* liste
)   :   _menueliste(liste)
{
    _titel = titel;
}

void EntrySubmenu::execute()
{
    MenuPresenter::instance()->updateList(_menueliste);
}

//QString EntrySubmenu::string()
//{
//    ostringstream ss;
//    ss << "<Untermenue ";
//    ss << "titel=\"" << xmlescape(_titel) << "\">\n";
//    ss << _menueliste->string() << "\n";
//    ss << "</Untermenue>";
//    return ss.str();
//}
