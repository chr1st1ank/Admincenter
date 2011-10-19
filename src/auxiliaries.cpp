#include <string>
#include <sstream>
#include "auxiliaries.hpp"

using namespace std;

/***************************************************************/
// Aus einem String einen integer machen
/***************************************************************/
string IntToString(const int& d)
{
    std::ostringstream w;
    w << d;
    return w.str();
}

/***************************************************************/
// Aus einer Zahl als unsigned int einen char machen
/***************************************************************/
char digitToChar(unsigned d)
{
    switch(d)
    {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        default:
            return 0;
    }
}

/***************************************************************/
// Eine Ziffer als Char in einen unsigned int verwandeln
/***************************************************************/
unsigned int CharToInt(const char& c)
{
    switch(c)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return 10;
    }
}

#include <map>
#include <boost/foreach.hpp>
std::string xmlescape(std::string s){
    std::map<std::string,std::string> m;
    m.insert(std::make_pair("&amp;","___(AMP)___"));
    m.insert(std::make_pair("&apos;","___(APOS)___"));
    m.insert(std::make_pair("&quot;","___(QUOT)___"));
    m.insert(std::make_pair("&lt;","___(LT)___"));
    m.insert(std::make_pair("&gt;","___(GT)___"));

    m.insert(std::make_pair("&","&amp;"));

    m.insert(std::make_pair("___(AMP)___","&amp;"));
    m.insert(std::make_pair("___(APOS)___","&apos;"));
    m.insert(std::make_pair("___(QUOT)___","&quot;"));
    m.insert(std::make_pair("___(LT)___","&lt;"));
    m.insert(std::make_pair("___(GT)___","&gt;"));

    m.insert(std::make_pair("'","&apos;"));
    m.insert(std::make_pair("\"","&quot;"));
    m.insert(std::make_pair("<","&lt;"));
    m.insert(std::make_pair(">","&gt;"));
    typedef std::pair<std::string,std::string> pair;
    BOOST_FOREACH( pair p, m)
    {
        size_t pos = s.find(p.first, 0);
        while(pos!=std::string::npos)
        {
            s = s.erase(pos, p.first.size());
            s = s.insert(pos,p.second);
            pos = s.find(p.first, ++pos);
        }
    }
    return s;
}
