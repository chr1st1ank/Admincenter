#include <iostream>
//#include <string>
#include <sstream>
#include <vector>
#include <fstream>

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _WIN32
#define WINVER 0x0500
#include <windows.h>
#include <tchar.h>
#include <direct.h>
#endif

#include "OperatingSystem.hpp"
#include "auxiliaries.hpp"
//#include "ui.hpp"
#include <exception>

// Maybe it's better to use Qt than the Winapi?
#include <QApplication>

using std::string;
using namespace std;
using namespace OperatingSystem;
using namespace OperatingSystem::privat;

void OperatingSystem::fehlermeldung(std::string Text, std::string Titel)
{
#ifdef _WIN32
    MessageBox( NULL, (LPTSTR)Text.c_str(), (LPTSTR)Titel.c_str()
              , MB_OK | MB_SETFOREGROUND | MB_ICONEXCLAMATION);
#else
#endif
}
void OperatingSystem::fehlermeldung(DWORD fehlernummer)
{
#ifdef _WIN32
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        fehlernummer,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
    );
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, NULL, MB_OK | MB_SETFOREGROUND | MB_ICONEXCLAMATION);
    LocalFree(lpMsgBuf);
#else
#endif
}
std::string OperatingSystem::fehlertext(DWORD fehlernummer)
{
#ifdef _WIN32
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        fehlernummer,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
    );
//    std::string text((LPCTSTR)lpMsgBuf); //TODO:OK so?
    std::string text(static_cast<char*>(lpMsgBuf));
    LocalFree(lpMsgBuf);
    return text;
#else
    return std::string("Dummyfehlermeldung!");
#endif
}
/***************************************************************/
// Aus einem String einen WCHAR-String machen
/***************************************************************/
void OperatingSystem::privat::StringToWCHAR(const std::string& s, WCHAR ws[max_stringlaenge])
{
#ifdef _WIN32
    const char* cs = s.c_str();
    MultiByteToWideChar(CP_OEMCP        //UINT CodePage
                        ,MB_PRECOMPOSED //DWORD dwFlags
                        ,cs             //LPCSTR lpMultiByteStr
                        ,-1             //int cbMultiByte
                        ,ws             //LPWSTR lpWideCharStr
                        ,max_stringlaenge);          //int cchWideChar
#else
#endif
}

/***************************************************************/
// Aus einem WCHAR-String einen String machen
// !!! Achtung: funktioniert noch nicht !!!
/***************************************************************/
std::string OperatingSystem::privat::WCHARToString(WCHAR* ws)
{
#ifdef _WIN32
    char cs[max_stringlaenge];
    int len = WideCharToMultiByte(
      CP_OEMCP          //UINT CodePage,
      ,MB_PRECOMPOSED   //DWORD dwFlags,
      ,ws               //LPCWSTR lpWideCharStr,
      ,-1               //int cchWideChar,
      ,cs               //LPSTR lpMultiByteStr,
      ,max_stringlaenge //int cbMultiByte,
      ,0                //LPCSTR lpDefaultChar,
      ,0                //LPBOOL lpUsedDefaultChar
    );
    return std::string(cs, len);
#else
    return std::string("Dummytext aus WCHARToString");
#endif
}

/***************************************************************/
// Aus einem TCHAR-String einen String machen
/***************************************************************/
std::string OperatingSystem::privat::TCHARToString(TCHAR* tc)
{
#ifdef _WIN32
#ifdef UNICODE
    return WCHARToString(tc);
#else
    return std::string(tc);
#endif
#else
    return std::string(*tc);
#endif
}

/***************************************************************/
// Aktueller Arbeitsordner
/***************************************************************/
string OperatingSystem::get_cd()
{
#ifdef _WIN32
    char arbeitsordner[max_stringlaenge];
    _getcwd(arbeitsordner, max_stringlaenge);
    string ao(arbeitsordner);
    return ao+"\\";
#else
    return(".");
#endif
}

/***************************************************************/
// Name der laufenden Anwendung
/***************************************************************/
std::string OperatingSystem::get_appname()
{
//    return QCoreApplication::instance()->applicationName().toStdString();
#ifdef _WIN32
    char szAppPath[MAX_PATH] = "";
//    WCHAR szAppPath[MAX_PATH] = "";//TODO: ok so?
    DWORD len = GetModuleFileName(0, szAppPath, sizeof(szAppPath) - 1);

    // Extract executable name
    std::string strAppDirectory(szAppPath, static_cast<size_t>(len));
    return strAppDirectory.substr(strAppDirectory.rfind("\\") + 1, strAppDirectory.length());
#else
    return "Appname";
#endif
}

/***************************************************************/
// Verzeichnis in welchem sich die laufende Anwendung befindet
/***************************************************************/
std::string OperatingSystem::get_appdir()
{
    return QCoreApplication::instance()->applicationDirPath().toStdString();
//#ifdef _WIN32
//    char szAppPath[MAX_PATH] = "";
//    DWORD len = GetModuleFileName(0, szAppPath, sizeof(szAppPath) - 1);
//
//    // Extract directory
//    std::string strAppDirectory(szAppPath, static_cast<size_t>(len));
//    return strAppDirectory.substr(0, strAppDirectory.rfind("\\"));
//#else
//    return ".";
//#endif
}



/***************************************************************/
// Aktueller User sammt Domain
/***************************************************************/
bool OperatingSystem::get_user(std::string& Name, std::string& Domain)
{
#ifdef _WIN32
    SID_NAME_USE snu;
    TOKEN_USER* ptu;
    HANDLE hProcessToken;
    DWORD dwLen = 0, cbAccountName, cbDomainName;
    TCHAR szAccountName[max_stringlaenge], szDomainName[max_stringlaenge];

    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hProcessToken))
    {
        GetTokenInformation(hProcessToken, TokenUser, NULL, 0, &dwLen);

        if((dwLen) && (NULL != (ptu = (TOKEN_USER*)HeapAlloc(GetProcessHeap(),
                           0, dwLen))))
        {
            if(GetTokenInformation(hProcessToken, TokenUser, (PVOID)ptu,
                                dwLen, &dwLen))
            {
                cbAccountName = sizeof((szAccountName)) / sizeof((szAccountName)[0]);
                cbDomainName = sizeof((szDomainName)) / sizeof((szDomainName)[0]);

                if(LookupAccountSid(NULL, ptu->User.Sid, szAccountName,
                               &cbAccountName, szDomainName,
                               &cbDomainName, &snu))
                {
                    Name = TCHARToString(szAccountName);
                    Domain = TCHARToString(szDomainName);
                }
                else
                {
                    fehlermeldung(GetLastError());
                    return false;
                }
            }
            else
            {
                fehlermeldung(GetLastError());
                return false;
            }
            HeapFree(GetProcessHeap(), 0, (PVOID)ptu);
        }
    CloseHandle(hProcessToken);
    }
    else
    {
        fehlermeldung(GetLastError());
        return false;
    }
    return true;
#else
    return true;
#endif
}
/***************************************************************/
// Rückgabe der lokalen Benutzerkonten
/***************************************************************/
vector<string> OperatingSystem::lokale_benutzer()
{
    vector<string> liste;
#ifdef _WIN32
    system("net users > benutzerliste.dat");
    ifstream datei("benutzerliste.dat");
    bool lesen = false;
    while(datei && !datei.eof())
    {
        string zeile;
        datei >> zeile;
        if(zeile == "Der")
            lesen = false;

        if(lesen && zeile != "Gast"
                 && zeile != "Hilfeassistent"
                 && zeile != "SUPPORT_388945a0"){
            liste.push_back(zeile);
        }

        if(zeile == "-------------------------------------------------------------------------------")
            lesen = true;
    }
    datei.close();
    remove("benutzerliste.dat");
#else
    liste.push_back("Nutzer 1");
    liste.push_back("Nutzer 2");
    liste.push_back("Nutzer 3");
#endif
    return liste;
}
/***************************************************************/
//Funktion prüft, ob ein bestimmter Registry-Key vorhanden ist.
/***************************************************************/
//BOOL RegKeyExists(HKEY hKey, LPCTSTR lpSubKey)
//{
//    BOOL bRet;
//    HKEY hSubKey;
//    LONG lResult;
//
//    if(ERROR_SUCCESS != (lResult = RegOpenKeyEx(hKey, lpSubKey, 0, 0, &hSubKey)))
//    {
//        bRet = (ERROR_FILE_NOT_FOUND == lResult) ? FALSE : TRUE;
//    }
//    else
//    {
//        RegCloseKey(hSubKey);
//        bRet = TRUE;
//    }
//
//return(bRet);
//}

/***************************************************************/
// Ein Programm starten
/***************************************************************/
void OperatingSystem::programm_starten(const string& sdateiname
                    , const string& sparameter
                    , const string& spfad       // = NULL
                    , bool unsichtbar)   // = false
{
#ifdef _WIN32
    // Die übergebenen C++-Strings in C-Strings verwandeln
    const char* pdatei = sdateiname.c_str();
    const char* pparameter = sparameter.c_str();
    const char* ppfad = spfad.c_str();

    int sichtbarkeit = unsichtbar ? SW_HIDE : SW_SHOWNORMAL;

    HINSTANCE i=ShellExecute(NULL,NULL,pdatei,pparameter,ppfad,sichtbarkeit);

    if(int(i)<=32) {
        //ShellExecute meldet einen Fehler
        ostringstream ss;
        ss << "Problem beim Starten des Programms:" << std::endl;
        ss << fehlertext(GetLastError()) << std::endl;
        ss << "Dateiname: \"" << sdateiname << "\"" << std::endl;
        ss << "Pfad: \"" << spfad << "\"" << std::endl;
        ss << "Parameter: \"" << sparameter << "\"" << std::endl;
        fehlermeldung(ss.str(),"Fehler");
    }
#else
#endif
}

/***************************************************************/
// Einen Prozess starten
/***************************************************************/
void OperatingSystem::prozess_starten(const string& sdateiname
                    , const string& sparameter
                    , const string& spfad       // = NULL
                    , bool unsichtbar)   // = false
{
#ifdef _WIN32
    string Kommandozeile = spfad + sdateiname + sparameter;

    CHAR* pKommandozeile = (CHAR*)Kommandozeile.c_str();
    CHAR* ppfad = (CHAR*)spfad.c_str();
    SECURITY_ATTRIBUTES sa;
        sa.nLength=sizeof(sa);
    STARTUPINFO si;
        si.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        si.wShowWindow=SW_SHOWNORMAL;
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
        ZeroMemory( &pi, sizeof(pi) );
    CreateProcess( NULL      //LPCTSTR lpApplicationName,
                 , pKommandozeile      //LPTSTR lpCommandLine,
                 , &sa         //LPSECURITY_ATTRIBUTES lpProcessAttributes,
                 , &sa        //LPSECURITY_ATTRIBUTES lpThreadAttributes,
                 , TRUE        //BOOL bInheritHandles,
                 , 0           //DWORD dwCreationFlags,
                 , NULL        //LPVOID lpEnvironment,
                 , ppfad       //LPCTSTR lpCurrentDirectory,
                 , &si        //LPSTARTUPINFO lpStartupInfo,
                 , &pi);      //LPPROCESS_INFORMATION lpProcessInformation);
#else
#endif
}
/***************************************************************/
// Einen Prozess unter anderem Benutzernamen starten
/***************************************************************/
//#include <locale>
//#include <iostream>
//bool NT4RunAsUser(const string& UserName,
//                const string& Password,
//                const string& DomainName,
//                const string& CommandLine,
//                const string& CurrentDirectory)
//{
//    bool returnvalue = true;
////    WCHAR wBenutzername[max_stringlaenge];
////        StringToWCHAR(Benutzername,wBenutzername);
////    WCHAR wDomain[max_stringlaenge];
////        StringToWCHAR(Domain,wDomain);
////    WCHAR wPasswort[max_stringlaenge];
////        StringToWCHAR(Passwort,wPasswort);
////    string Kommandozeile = Pfad + Dateiname + Parameter;
////        WCHAR wKommandozeile[max_stringlaenge];
////        StringToWCHAR(Kommandozeile,wKommandozeile);
//    STARTUPINFO si;
//        si.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
//        si.wShowWindow=SW_SHOWNORMAL;
//        ZeroMemory( &si, sizeof(si) );
//        si.cb = sizeof(si);
//    PROCESS_INFORMATION pi;
//        ZeroMemory( &pi, sizeof(pi) );
////    WCHAR wArbeitspfad[max_stringlaenge];
////        StringToWCHAR(Pfad,wArbeitspfad);
//
//    HANDLE hFirstToken;
//
//    int Result = LogonUser(
//        (CHAR*)UserName.c_str(),
//        (CHAR*)DomainName.c_str(),
//        (CHAR*)Password.c_str(),
//        LOGON32_LOGON_INTERACTIVE, LOGON32_PROVIDER_DEFAULT, &hFirstToken);
//    if(Result == 0)
//    {
//        //        ' LogonUser will fail with 1314 error code, if the user account associated
//        //        ' with the calling security context does not have
//        //        ' "Act as part of the operating system" permission
//        ostringstream ss;
//        ss << "Problem beim Starten des Programms." << std::endl;
//        ss << fehlertext(GetLastError()) << std::endl;
//        fehlermeldung(ss.str(),"Fehler");
//        returnvalue = false;
//    }
//    HANDLE hToken;
//    SECURITY_ATTRIBUTES sa;
//    sa.bInheritHandle       = false;
//    sa.nLength              = sizeof(sa);
//    sa.lpSecurityDescriptor = 0;
//    Result = DuplicateTokenEx(&hFirstToken, GENERIC_ALL, &sa, SecurityImpersonation, TokenPrimary, &hToken);
//    if(Result == 0)
//    {
//        ostringstream ss;
//        ss << "Token duplication failed." << std::endl;
//        ss << fehlertext(GetLastError()) << std::endl;
//        fehlermeldung(ss.str(),"Fehler");
//        return false;
//    }
//    CloseHandle(hFirstToken);
//
//    Result = ImpersonateLoggedOnUser(hToken);
//    if(Result == 0)
//    {
//        ostringstream ss;
//        ss << "Impersonation failed." << std::endl;
//        ss << fehlertext(GetLastError()) << std::endl;
//        fehlermeldung(ss.str(),"Fehler");
//        return false;
//    }
//
//    Result = CreateProcessAsUser(hToken, 0, (CHAR*)CommandLine.c_str(), 0, 0, false,
//                CREATE_DEFAULT_ERROR_MODE,
//                0, (CHAR*)CurrentDirectory.c_str(), &si, &pi);
//    if(Result == 0)
//    {
//        //' CreateProcessAsUser will fail with 1314 error code, if the user
//        //' account associated with the calling security context does not have
//        //' the following two permissions
//        ostringstream ss;
//        ss << "Problem beim Starten des Programms." << std::endl;
//        ss << fehlertext(GetLastError()) << std::endl;
//        fehlermeldung(ss.str(),"Fehler");
//        returnvalue = false;
//    }
//
//    CloseHandle(pi.hProcess);
//    CloseHandle(pi.hThread);
//    CloseHandle(hToken);
//    return returnvalue;
//}

bool OperatingSystem::prozess_starten_als(const string& Benutzername, const string& Domain, const string& Passwort
                        ,const string& Dateiname, const string& _Parameter, const string& _Pfad)
{
#ifdef _WIN32
    string pfad = _Pfad;
    if(*pfad.begin() == '"' && *pfad.rbegin() == '"')
        pfad = pfad.substr(1, pfad.length() - 2);
    if(*pfad.rbegin() == '\\')
        pfad = pfad.substr(0, pfad.length() - 2);
    string parameter;
    if(*_Parameter.begin() == ' ')
        parameter = _Parameter;
    else
        parameter = ' ' + _Parameter;

    bool returnvalue = true;
    WCHAR wBenutzername[max_stringlaenge];
        StringToWCHAR(Benutzername,wBenutzername);
    WCHAR wDomain[max_stringlaenge];
        StringToWCHAR(Domain,wDomain);
    WCHAR wPasswort[max_stringlaenge];
        StringToWCHAR(Passwort,wPasswort);
    WCHAR wApplicationName[max_stringlaenge];
        StringToWCHAR(Dateiname,wApplicationName);
    string Kommandozeile = '"' + pfad + '\\' + Dateiname + '"' + parameter;
        WCHAR wKommandozeile[max_stringlaenge];
        StringToWCHAR(Kommandozeile,wKommandozeile);
    PROCESS_INFORMATION pi;
        memset(&pi, 0, sizeof(pi));
    STARTUPINFOW si;
        si.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        si.wShowWindow=SW_SHOWNORMAL;
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
    WCHAR wArbeitspfad[max_stringlaenge];
        StringToWCHAR(pfad,wArbeitspfad);

    if(!CreateProcessWithLogonW( wBenutzername, wDomain, wPasswort
                               , LOGON_WITH_PROFILE, wApplicationName
                               , wKommandozeile, CREATE_NEW_CONSOLE, NULL, wArbeitspfad
                               , &si, &pi))
    {
        ostringstream ss;
        ss << "Problem beim Starten des Programms:" << std::endl;
        ss << fehlertext(GetLastError()) << std::endl;
        ss << "Dateiname: \"" << Dateiname << "\"" << std::endl;
        ss << "Pfad: \"" << _Pfad << "\"" << std::endl;
        ss << "Parameter: \"" << _Parameter << "\"" << std::endl;
        fehlermeldung(ss.str(),"Fehler");
        returnvalue = false;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return returnvalue;
#else
    return true;
#endif
}

