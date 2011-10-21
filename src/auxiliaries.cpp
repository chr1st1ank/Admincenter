//#include <string>
//#include <sstream>
#include "auxiliaries.hpp"

using namespace std;

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
            return '?';
    }
}

///***************************************************************/
//// Eine Ziffer als Char in einen unsigned int verwandeln
///***************************************************************/
//unsigned int CharToInt(const char& c)
//{
//    switch(c)
//    {
//        case '0':
//            return 0;
//        case '1':
//            return 1;
//        case '2':
//            return 2;
//        case '3':
//            return 3;
//        case '4':
//            return 4;
//        case '5':
//            return 5;
//        case '6':
//            return 6;
//        case '7':
//            return 7;
//        case '8':
//            return 8;
//        case '9':
//            return 9;
//        default:
//            return 10;
//    }
//}

QString xmlescape(QString s)
{
    s = s.replace(QString("&amp;"),QString("___(AMP)___"));
    s = s.replace(QString("&apos;"),QString("___(APOS)___"));
    s = s.replace(QString("&quot;"),QString("___(QUOT)___"));
    s = s.replace(QString("&lt;"),QString("___(LT)___"));
    s = s.replace(QString("&gt;"),QString("___(GT)___"));

    s = s.replace(QString("&"),QString("&amp;"));

    s = s.replace(QString("___(AMP)___"),QString("&amp;"));
    s = s.replace(QString("___(APOS)___"),QString("&apos;"));
    s = s.replace(QString("___(QUOT)___"),QString("&quot;"));
    s = s.replace(QString("___(LT)___"),QString("&lt;"));
    s = s.replace(QString("___(GT)___"),QString("&gt;"));

    s = s.replace(QString("'"),QString("&apos;"));
    s = s.replace(QString("\""),QString("&quot;"));
    s = s.replace(QString("<"),QString("&lt;"));
    s = s.replace(QString(">"),QString("&gt;"));
}
