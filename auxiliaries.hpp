#ifndef WCHAR_H
#define WCHAR_H

//#include <windows.h>
#include <string>

// Aus einem String einen integer machen
    std::string IntToString(const int& d);

// Aus einer Zahl als unsigned int einen char machen
char digitToChar(unsigned d);

// Eine Ziffer als Char in einen unsigned int verwandeln
    unsigned int CharToInt(const char& c);

std::string xmlescape(std::string s);

#endif
