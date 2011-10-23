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
#include "debug.h"
//#include "ui.hpp"
#include <exception>

// Maybe it's better to use Qt than the Winapi?
#include <QApplication>
#include <QString>

using std::string;
using namespace std;
using namespace OperatingSystem;
using namespace OperatingSystem::privat;

QString OperatingSystem::Path::sep()
{
#ifdef _WIN32
    return QString("\\");
#else
//    const QString OperatingSystem::Path::sep = QString("/");
    return QString("/");
#endif
}

QString OperatingSystem::Path::join(const QString& path1, const QString& path2)
{
    if(path1.endsWith(OperatingSystem::Path::sep()) && !path2.startsWith(OperatingSystem::Path::sep()))
        return path1 + path2;
    return path1 + OperatingSystem::Path::sep() + path2;
}

//void OperatingSystem::fehlermeldung(std::string Text, std::string Titel)
//{
//#ifdef _WIN32
//    MessageBox( NULL, (LPTSTR)Text.c_str(), (LPTSTR)Titel.c_str()
//              , MB_OK | MB_SETFOREGROUND | MB_ICONEXCLAMATION);
//#else
//#endif
//}
//void OperatingSystem::fehlermeldung(DWORD fehlernummer)
//{
//#ifdef _WIN32
//    LPVOID lpMsgBuf;
//    FormatMessage(
//        FORMAT_MESSAGE_ALLOCATE_BUFFER |
//        FORMAT_MESSAGE_FROM_SYSTEM |
//        FORMAT_MESSAGE_IGNORE_INSERTS,
//        NULL,
//        fehlernummer,
//        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//        (LPTSTR) &lpMsgBuf,
//        0,
//        NULL
//    );
//    MessageBox(NULL, (LPCTSTR)lpMsgBuf, NULL, MB_OK | MB_SETFOREGROUND | MB_ICONEXCLAMATION);
//    LocalFree(lpMsgBuf);
//#else
//#endif
//}
QString OperatingSystem::errorMessage(DWORD errorid)
{
#ifdef _WIN32
    LPTSTR lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorid,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        lpMsgBuf,
        0,
        NULL
    );
//    std::string text((LPCTSTR)lpMsgBuf); //TODO:OK so?
    QString text = QString::fromLocal8Bit(lpMsgBuf);
    LocalFree(lpMsgBuf);
    return text;
#else
    return QString("Error with id ")+ QString::number(errorid);
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
    unsigned i = 0;
    for(std::string::const_iterator it=s.begin(); it!=s.end(); ++it)
    {
        if(i > max_stringlaenge)
            return;
        ws[i] = *it;
    }
#endif
}

void OperatingSystem::privat::QStringToWCHAR(const QString& s, WCHAR ws[max_stringlaenge])
{
    if(static_cast<size_t>(s.size()) > max_stringlaenge)
    {
        s.left(max_stringlaenge - 1).toWCharArray(ws);
        return;
    }
    s.toWCharArray(ws);
//#ifdef _WIN32
//    const char* cs = s.c_str();
//    MultiByteToWideChar(CP_OEMCP        //UINT CodePage
//                        ,MB_PRECOMPOSED //DWORD dwFlags
//                        ,cs             //LPCSTR lpMultiByteStr
//                        ,-1             //int cbMultiByte
//                        ,ws             //LPWSTR lpWideCharStr
//                        ,max_stringlaenge);          //int cchWideChar
//#else
//#endif
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
    return std::string(QString::fromWCharArray(ws).toLocal8Bit().constData());
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
    return std::string(tc);
#endif
}

void throwError(DWORD errorid)
{
    throw OSError(errorMessage(errorid));
}

/***************************************************************/
// Aktueller Arbeitsordner
/***************************************************************/
QString OperatingSystem::get_cd()
{
#ifdef _WIN32
    char workingdir[max_stringlaenge];
    _getcwd(workingdir, max_stringlaenge);
    QString ao = QString::fromLocal8Bit(workingdir);
    return Path::join(ao, Path::sep);
#else
    return(".");
#endif
}

/***************************************************************/
// Name der laufenden Anwendung
/***************************************************************/
QString OperatingSystem::get_appname()
{
#ifdef _WIN32
    char szAppPath[MAX_PATH] = "";
//    WCHAR szAppPath[MAX_PATH] = "";//TODO: ok so?
    DWORD len = GetModuleFileName(0, szAppPath, sizeof(szAppPath) - 1);

    // Extract executable name
    std::string strAppDirectory(szAppPath, static_cast<size_t>(len));
    return QString::fromLocal8Bit(strAppDirectory.substr(strAppDirectory.rfind("\\") + 1, strAppDirectory.length()));
#else
    return QCoreApplication::instance()->applicationName();
#endif
}

/***************************************************************/
// Verzeichnis in welchem sich die laufende Anwendung befindet
/***************************************************************/
QString OperatingSystem::get_appdir()
{
    return QCoreApplication::instance()->applicationDirPath();
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
bool OperatingSystem::get_user(QString& Name, QString& Domain)
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
                    Name = QString::fromLocal8Bit(szAccountName);
                    Domain = QString::fromLocal8Bit(szDomainName);
                }
                else
                {
                    throwError(GetLastError());
                }
            }
            else
            {
                throwError(GetLastError());
            }
            HeapFree(GetProcessHeap(), 0, (PVOID)ptu);
        }
    CloseHandle(hProcessToken);
    }
    else
    {
        throwError(GetLastError());
    }
    return true;
#else
    Name = "Dummyname";
    Domain = "Dummydomain";
    return true;
#endif
}
/***************************************************************/
// Rückgabe der lokalen Benutzerkonten
/***************************************************************/
vector<QString> OperatingSystem::local_users()
{
    vector<QString> liste;
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
            liste.push_back(QString::fromLocal8Bit(zeile));
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
void OperatingSystem::programm_starten(const QString& sdateiname
                    , const QString& sparameter
                    , const QString& spfad       // = NULL
                    , bool invisible)   // = false
{
#ifdef _WIN32
    int sichtbarkeit = invisible ? SW_HIDE : SW_SHOWNORMAL;

    HINSTANCE i=ShellExecute(NULL,NULL,sdateiname.local8Bit().constData(),
                             sparameter.local8Bit().constData(),
                             spfad.local8Bit().constData(),sichtbarkeit);

    if(int(i)<=32) {
        //ShellExecute meldet einen Fehler
        ostringstream ss;
        ss << "Problem beim Starten des Programms:" << std::endl;
        ss << errorMessage(GetLastError()).toLocal8Bit().constData() << std::endl;
        ss << "Dateiname: \"" << sdateiname.toLocal8Bit().constData() << "\"" << std::endl;
        ss << "Pfad: \"" << spfad.toLocal8Bit().constData() << "\"" << std::endl;
        ss << "Parameter: \"" << sparameter.toLocal8Bit().constData() << "\"" << std::endl;
        ss << "Invisible: \"" << (invisible ? "True" : "False") << "\"" << std::endl;
//        fehlermeldung(ss.str(),"Fehler");
    }
#else
    ostringstream ss;
    ss << "Starten des Programms:" << std::endl;
    ss << "Dateiname: \"" << sdateiname.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Pfad: \"" << spfad.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Parameter: \"" << sparameter.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Invisible: \"" << (invisible ? "True" : "False") << "\"" << std::endl;
    cDEBUG(ss.str());
#endif
}

/***************************************************************/
// Einen Prozess starten
/***************************************************************/
void OperatingSystem::prozess_starten(const QString& sdateiname
                    , const QString& sparameter
                    , const QString& spfad       // = NULL
                    , bool invisible)   // = false
{
#ifdef _WIN32
    QString commandLine = path.join(spfad,sdateiname) + " " + sparameter;

    // TODO: Very ugly to cast the const pointers to non-const!
    CHAR* pcommandLine = (CHAR*)commandLine.local8Bit().constData();
    CHAR* ppfad = (CHAR*)spfad.local8Bit().constData();
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
                 , pcommandLine      //LPTSTR lpCommandLine,
                 , &sa         //LPSECURITY_ATTRIBUTES lpProcessAttributes,
                 , &sa        //LPSECURITY_ATTRIBUTES lpThreadAttributes,
                 , TRUE        //BOOL bInheritHandles,
                 , 0           //DWORD dwCreationFlags,
                 , NULL        //LPVOID lpEnvironment,
                 , ppfad       //LPCTSTR lpCurrentDirectory,
                 , &si        //LPSTARTUPINFO lpStartupInfo,
                 , &pi);      //LPPROCESS_INFORMATION lpProcessInformation);
#else
    ostringstream ss;
    ss << "Starting process:" << std::endl;
    ss << "Dateiname: \"" << sdateiname.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Pfad: \"" << spfad.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Parameter: \"" << sparameter.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Invisible: \"" << (invisible ? "True" : "False") << "\"" << std::endl;
    cDEBUG(ss.str());
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

bool OperatingSystem::prozess_starten_als(const QString& Benutzername, const QString& Domain, const QString& Passwort
                        ,const QString& Dateiname, const QString& _Parameter, const QString& _Pfad)
{
#ifdef _WIN32
    QString path = _Pfad;
    // Cut quotes from begin and end
    if(path.startsWith('"') && path.endsWith('"'))
        path = path.mid(1, path.size() - 2)
    // Chop a separator from the end
    if(path.endsWith(path.sep))
        path.chop(1);
    QString parameter;
    if(_Parameter.startsWith(' '))
        parameter = _Parameter;
    else
        parameter = ' ' + _Parameter;

    bool returnvalue = true;
    WCHAR wBenutzername[max_stringlaenge];
        QStringToWCHAR(Benutzername,wBenutzername);
    WCHAR wDomain[max_stringlaenge];
        QStringToWCHAR(Domain,wDomain);
    WCHAR wPasswort[max_stringlaenge];
        QStringToWCHAR(Passwort,wPasswort);
    WCHAR wApplicationName[max_stringlaenge];
        QStringToWCHAR(Dateiname,wApplicationName);
    QString commandLine = '"' + path.join(path,Dateiname) + '"' + parameter;
        WCHAR wCommandLine[max_stringlaenge];
        QStringToWCHAR(commandLine,wCommandLine);
    PROCESS_INFORMATION pi;
        memset(&pi, 0, sizeof(pi));
    STARTUPINFOW si;
        si.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        si.wShowWindow=SW_SHOWNORMAL;
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
    WCHAR wWorkingPath[max_stringlaenge];
        QStringToWCHAR(path,wWorkingPath);

    if(!CreateProcessWithLogonW( wBenutzername, wDomain, wPasswort
                               , LOGON_WITH_PROFILE, wApplicationName
                               , wCommandLine, CREATE_NEW_CONSOLE, NULL, wWorkingPath
                               , &si, &pi))
    {
        ostringstream ss;
        ss << "Problem beim Starten des Programms:" << std::endl;
        ss << fehlertext(GetLastError()) << std::endl;
        ss << "Dateiname: \"" << Dateiname << "\"" << std::endl;
        ss << "Pfad: \"" << _Pfad << "\"" << std::endl;
        ss << "Parameter: \"" << _Parameter << "\"" << std::endl;
//        fehlermeldung(ss.str(),"Fehler");
        returnvalue = false;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return returnvalue;
#else
    ostringstream ss;
    ss << "Starting process:" << std::endl;
    ss << "As user: \"" << Benutzername.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Dateiname: \"" << Dateiname.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Pfad: \"" << _Pfad.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Parameter: \"" << _Parameter.toLocal8Bit().constData() << "\"" << std::endl;
    cDEBUG(ss.str());
    return true;
#endif
}

