
#include "EntrySubmenu.hpp"
#include "MenuPresenter.hpp"
#include "auxiliaries.hpp"

#include <string>
#include <sstream>

using std::string;
using namespace std;

/************************************************
* EntrySubmenu
************************************************/
EntrySubmenu::EntrySubmenu(
    const std::string& titel,
    Menulist* liste
)   :   _menueliste(liste)
{
    _titel = titel;
}

void EntrySubmenu::execute()
{
    MenuPresenter::instance()->updateList(_menueliste);
}

std::string EntrySubmenu::string()
{
    ostringstream ss;
    ss << "<Untermenue ";
    ss << "titel=\"" << xmlescape(_titel) << "\">\n";
    ss << _menueliste->string() << "\n";
    ss << "</Untermenue>";
    return ss.str();
}
