#ifndef AUXILIARIES_HPP
#define AUXILIARIES_HPP

#include <QString>

// Aus einer Zahl als unsigned int einen char machen
char digitToChar(unsigned d);

//// Eine Ziffer als Char in einen unsigned int verwandeln
//    unsigned int CharToInt(const char& c);

QString xmlescape(QString s);

#endif //AUXILIARIES_HPP
