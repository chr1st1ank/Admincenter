#include <iostream>
//#include <string>
#include <sstream>
#include <vector>
#include <fstream>

//#ifdef UNICODE
//#undef UNICODE
//#endif

#ifdef _WIN32
#ifndef UNICODE
#define UNICODE
#endif
#define WINVER 0x0500
#include <windows.h>
//#include <lm.h>
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
//    LPWSTR lpMsgBuf[max_stringlaenge];
    WCHAR lpMsgBuf[max_stringlaenge];
    FormatMessageW(
        //FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorid,
        MAKELANGID(LANG_SYSTEM_DEFAULT,SUBLANG_SYS_DEFAULT),//MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        lpMsgBuf,
        max_stringlaenge,
        NULL
    );
    QString text = QString::fromWCharArray(lpMsgBuf);
    LocalFree(lpMsgBuf);
    return text;
#else
    return QString("Error with id ")+ QString::number(errorid);
#endif
}
///***************************************************************/
//// Aus einem String einen WCHAR-String machen
///***************************************************************/
//void OperatingSystem::privat::StringToWCHAR(const std::string& s, WCHAR ws[max_stringlaenge])
//{
//#ifdef _WIN32
//    const char* cs = s.c_str();
//    MultiByteToWideChar(CP_OEMCP        //UINT CodePage
//                        ,MB_PRECOMPOSED //DWORD dwFlags
//                        ,cs             //LPCSTR lpMultiByteStr
//                        ,-1             //int cbMultiByte
//                        ,ws             //LPWSTR lpWideCharStr
//                        ,max_stringlaenge);          //int cchWideChar
//#else
//    unsigned i = 0;
//    for(std::string::const_iterator it=s.begin(); it!=s.end(); ++it)
//    {
//        if(i > max_stringlaenge)
//            return;
//        ws[i] = *it;
//    }
//#endif
//}

//void OperatingSystem::privat::QStringToWCHAR(const QString& s, WCHAR ws[max_stringlaenge])
void OperatingSystem::privat::QStringToWCHAR(const QString& s, WCHAR ws[], int ws_length)
{
    if(ws_length <= 0)
        return;
    QString mod = s.left(ws_length - 1) + QChar('\0');
    mod.toWCharArray(ws);
}

///***************************************************************/
//// Aus einem WCHAR-String einen String machen
//// !!! Achtung: funktioniert noch nicht !!!
///***************************************************************/
//std::string OperatingSystem::privat::WCHARToString(WCHAR* ws)
//{
//#ifdef _WIN32
//    char cs[max_stringlaenge];
//    int len = WideCharToMultiByte(
//      CP_OEMCP          //UINT CodePage,
//      ,MB_PRECOMPOSED   //DWORD dwFlags,
//      ,ws               //LPCWSTR lpWideCharStr,
//      ,-1               //int cchWideChar,
//      ,cs               //LPSTR lpMultiByteStr,
//      ,max_stringlaenge //int cbMultiByte,
//      ,0                //LPCSTR lpDefaultChar,
//      ,0                //LPBOOL lpUsedDefaultChar
//    );
//    return std::string(cs, len);
//#else
//    return std::string(QString::fromWCharArray(ws).toLocal8Bit().constData());
//#endif
//}
//
///***************************************************************/
//// Aus einem TCHAR-String einen String machen
///***************************************************************/
//std::string OperatingSystem::privat::TCHARToString(TCHAR* tc)
//{
//#ifdef _WIN32
//#ifdef UNICODE
//    return WCHARToString(tc);
//#else
//    return std::string(tc);
//#endif
//#else
//    return std::string(tc);
//#endif
//}

void OperatingSystem::privat::throwError(DWORD errorid)
{
    throw new OSError(errorMessage(errorid));
}

/***************************************************************/
// Aktueller Arbeitsordner
/***************************************************************/
QString OperatingSystem::get_cd()
{
#ifdef _WIN32
    wchar_t workingdir[max_stringlaenge];
    _wgetcwd(workingdir, max_stringlaenge);
    QString ao = QString::fromWCharArray(workingdir,max_stringlaenge);//TODO: Second parameter ok?
    return Path::join(ao, Path::sep());
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
    WCHAR szAppPath[MAX_PATH] = L"";//TODO: ok so?
    DWORD len = GetModuleFileNameW(0, szAppPath, MAX_PATH);

    // Extract executable name
    QString appDirectory = QString::fromWCharArray(szAppPath);
    int index = appDirectory.lastIndexOf(Path::sep());
    return appDirectory.right(appDirectory.size() - index - 1);
#else
    return QCoreApplication::instance()->applicationName();
#endif
}

/***************************************************************/
// Verzeichnis in welchem sich die laufende Anwendung befindet
/***************************************************************/
QString OperatingSystem::get_appdir()
{
#ifdef _WIN32
    WCHAR szAppPath[MAX_PATH] = L"";//TODO: ok so?
    DWORD len = GetModuleFileNameW(0, szAppPath, MAX_PATH);

    // Extract executable name
    QString appDirectory = QString::fromWCharArray(szAppPath);
    return appDirectory.left(appDirectory.lastIndexOf(Path::sep()));
#else
    return QCoreApplication::instance()->applicationDirPath();
#endif
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
    WCHAR szAccountName[max_stringlaenge], szDomainName[max_stringlaenge];

    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hProcessToken))
    {
//        BOOL WINAPI GetTokenInformation(
//          __in       HANDLE TokenHandle,
//          __in       TOKEN_INFORMATION_CLASS TokenInformationClass,
//          __out_opt  LPVOID TokenInformation,
//          __in       DWORD TokenInformationLength,
//          __out      PDWORD ReturnLength
//        );
        GetTokenInformation(hProcessToken, TokenUser, NULL, 0, &dwLen);

        if((dwLen) && (NULL != (ptu = (TOKEN_USER*)HeapAlloc(GetProcessHeap(), 0, dwLen))))
        {
            if(GetTokenInformation(hProcessToken, TokenUser, (PVOID)ptu,
                                dwLen, &dwLen))
            {
                cbAccountName = sizeof((szAccountName)) / sizeof((szAccountName)[0]);
                cbDomainName = sizeof((szDomainName)) / sizeof((szDomainName)[0]);

                if(LookupAccountSidW(NULL, ptu->User.Sid, szAccountName,
                               &cbAccountName, szDomainName,
                               &cbDomainName, &snu))
                {
                    Name = QString::fromWCharArray(szAccountName);
                    Domain = QString::fromWCharArray(szDomainName);
                }
                else
                {
                    CloseHandle(hProcessToken);
                    HeapFree(GetProcessHeap(), 0, (PVOID)ptu);
                    privat::throwError(GetLastError());
                }
            }
            else
            {
                CloseHandle(hProcessToken);
                HeapFree(GetProcessHeap(), 0, (PVOID)ptu);
                privat::throwError(GetLastError());
            }
            HeapFree(GetProcessHeap(), 0, (PVOID)ptu);
        }
    CloseHandle(hProcessToken);
    }
    else
    {
        privat::throwError(GetLastError());
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
    //TODO: Find another solution!!!
    vector<QString> liste;
#ifdef _WIN32
//NET_API_STATUS NetUserEnum(
//  __in     LPCWSTR servername,
//  __in     DWORD level,
//  __in     DWORD filter,
//  __out    LPBYTE *bufptr,
//  __in     DWORD prefmaxlen,
//  __out    LPDWORD entriesread,
//  __out    LPDWORD totalentries,
//  __inout  LPDWORD resume_handle
//);
//    LPBYTE *bufptr;
//    DWORD entriesread,totalentries;
//    NetUserEnum(NULL,0,0,bufptr,MAX_PREFERRED_LENGTH,&entriesread,&totalentries,NULL);
//    NetApiBufferFree(bufptr);

    system("net users > benutzerliste.dat");
    ifstream datei("benutzerliste.dat");
    bool lesen = false;
    while(datei && !datei.eof())
    {
        std::string zeile;
        datei >> zeile;
        if(zeile == "Der")
            lesen = false;

        if(lesen && zeile != "Gast"
                 && zeile != "Hilfeassistent"
                 && zeile != "SUPPORT_388945a0"){
            liste.push_back(QString::fromLocal8Bit(zeile.c_str()));
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
void OperatingSystem::programm_starten(const QString& sfilename
                    , const QString& sparameter
                    , const QString& spath       // = NULL
                    , bool invisible)   // = false
{
#ifdef _WIN32
    int sichtbarkeit = invisible ? SW_HIDE : SW_SHOWNORMAL;

    // Create wstrings
    WCHAR wfilename[sfilename.size()+1];
    WCHAR wparameter[sparameter.size()+1];
    WCHAR wpath[spath.size()+1];
    privat::QStringToWCHAR(sfilename,wfilename,sfilename.size()+1);
    privat::QStringToWCHAR(sparameter,wparameter,sparameter.size()+1);
    privat::QStringToWCHAR(spath,wpath,spath.size()+1);

    // Do execution
    HINSTANCE i=ShellExecuteW(NULL,NULL,wfilename,wparameter,wpath,sichtbarkeit);

    // Check for errors
    if(int(i)<=32) {
        //ShellExecute reports an error
        QString errorText = "Problem starting program: ";
        errorText.append(errorMessage(GetLastError()));
        errorText.append(" Filename: \"" + sfilename + "\"");
        errorText.append(" Path: \"" + spath + "\"");
        errorText.append(" Parameter: \"" + sparameter + "\"");
        errorText.append(" Invisible: \"" + (invisible ? QString("True") : QString("False")) + "\"");
        throw new OSError(errorText);
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

///***************************************************************/
//// Einen Prozess starten
///***************************************************************/
//void OperatingSystem::prozess_starten(const QString& sdateiname
//                    , const QString& sparameter
//                    , const QString& spfad       // = NULL
//                    , bool invisible)   // = false
//{
//    //TODO: Do we really need this?
//#ifdef _WIN32
//    QString commandLine = Path.join(spfad,sdateiname) + " " + sparameter;
//
//    // TODO: Very ugly to cast the const pointers to non-const!
//    CHAR* pcommandLine = (CHAR*)commandLine.toLocal8Bit().constData();
//    CHAR* ppfad = (CHAR*)spfad.toLocal8Bit().constData();
//    SECURITY_ATTRIBUTES sa;
//        sa.nLength=sizeof(sa);
//    STARTUPINFO si;
//        si.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
//        si.wShowWindow=SW_SHOWNORMAL;
//        ZeroMemory( &si, sizeof(si) );
//        si.cb = sizeof(si);
//    PROCESS_INFORMATION pi;
//        ZeroMemory( &pi, sizeof(pi) );
//    CreateProcess( NULL      //LPCTSTR lpApplicationName,
//                 , pcommandLine      //LPTSTR lpCommandLine,
//                 , &sa         //LPSECURITY_ATTRIBUTES lpProcessAttributes,
//                 , &sa        //LPSECURITY_ATTRIBUTES lpThreadAttributes,
//                 , TRUE        //BOOL bInheritHandles,
//                 , 0           //DWORD dwCreationFlags,
//                 , NULL        //LPVOID lpEnvironment,
//                 , ppfad       //LPCTSTR lpCurrentDirectory,
//                 , &si        //LPSTARTUPINFO lpStartupInfo,
//                 , &pi);      //LPPROCESS_INFORMATION lpProcessInformation);
//#else
//    ostringstream ss;
//    ss << "Starting process:" << std::endl;
//    ss << "Dateiname: \"" << sdateiname.toLocal8Bit().constData() << "\"" << std::endl;
//    ss << "Pfad: \"" << spfad.toLocal8Bit().constData() << "\"" << std::endl;
//    ss << "Parameter: \"" << sparameter.toLocal8Bit().constData() << "\"" << std::endl;
//    ss << "Invisible: \"" << (invisible ? "True" : "False") << "\"" << std::endl;
//    cDEBUG(ss.str());
//#endif
//}
/***************************************************************/
// Einen Prozess unter anderem Benutzernamen starten
/***************************************************************/
bool OperatingSystem::prozess_starten_als(const QString& Benutzername, const QString& Domain, const QString& Passwort
                        ,const QString& Dateiname, const QString& _Parameter, const QString& _Pfad)
{
    ostringstream ss;
    ss << "Starting process:" << std::endl;
    ss << "As user: \"" << Benutzername.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Dateiname: \"" << Dateiname.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Pfad: \"" << _Pfad.toLocal8Bit().constData() << "\"" << std::endl;
    ss << "Parameter: \"" << _Parameter.toLocal8Bit().constData() << "\"" << std::endl;
    cDEBUG(ss.str());
#ifdef _WIN32
    QString path = _Pfad;
    // Cut quotes from begin and end
    if(path.startsWith('"') && path.endsWith('"'))
        path = path.mid(1, path.size() - 2);
    // Chop a separator from the end
    if(path.endsWith(Path::sep()))
        path.chop(1);
    // Prepare parameters. We need a leading space.
    QString parameter;
    if(_Parameter.startsWith(' '))
        parameter = _Parameter;
    else
        parameter = ' ' + _Parameter;
    // Define the command line to be passed to the new process
    QString commandLine = '"' + Path::join(path,Dateiname) + '"' + parameter;

    bool returnvalue = true;
    WCHAR wBenutzername[Benutzername.size()+1];
    WCHAR wDomain[Domain.size()+1];
    WCHAR wPasswort[Passwort.size()+1];
    WCHAR wApplicationName[Dateiname.size()+1];
//    WCHAR wApplicationName[Path::join(path,Dateiname).size()+1];
    WCHAR wCommandLine[commandLine.size()+1];
    WCHAR wWorkingPath[path.size() + 1];

    QStringToWCHAR(Benutzername,wBenutzername,Benutzername.size()+1);
    QStringToWCHAR(Domain,wDomain,Domain.size()+1);
    QStringToWCHAR(Passwort,wPasswort,Passwort.size()+1);
    QStringToWCHAR(Dateiname,wApplicationName,Dateiname.size()+1);
//    QStringToWCHAR(Path::join(path,Dateiname),wApplicationName,Path::join(path,Dateiname).size()+1);
    QStringToWCHAR(commandLine,wCommandLine,commandLine.size()+1);
    QStringToWCHAR(path,wWorkingPath,path.size() + 1);

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));
    STARTUPINFOW si;
    si.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow=SW_SHOWNORMAL;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);

    if(!CreateProcessWithLogonW( wBenutzername, wDomain, wPasswort
                               , LOGON_WITH_PROFILE, wApplicationName
                               , wCommandLine, CREATE_NEW_CONSOLE, NULL, wWorkingPath
                               , &si, &pi))
    {
        QString errorText = "Problem starting a process: ";
        errorText.append(errorMessage(GetLastError()));
        errorText.append(" Username: \"" + QString::fromWCharArray(wBenutzername) + "\"");
        errorText.append(" Domain: \"" + QString::fromWCharArray(wDomain) + "\"");
        errorText.append(" Password: \"" + QString::fromWCharArray(wPasswort) + "\"");
        errorText.append(" Filename: \"" + QString::fromWCharArray(wApplicationName) + "\"");
        errorText.append(" Path: \"" + QString::fromWCharArray(wWorkingPath) + "\"");
        errorText.append(" Kommandozeile: \"" + QString::fromWCharArray(wCommandLine) + "\"");
//        throw OSError(errorText);
//        fehlermeldung(ss.str(),"Fehler");
        cDEBUG(errorText.toLocal8Bit().constData());
        returnvalue = false;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return returnvalue;
#else
    return true;
#endif
}

