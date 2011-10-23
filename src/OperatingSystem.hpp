#ifndef OPERATINGSYSTEM_HPP
#define OPERATINGSYSTEM_HPP

#include "BaseException.hpp"
//#include <string>
#include <vector>
#include <QString>

#ifdef _WIN32
#define WINVER 0x0500
#include <windows.h>
#else
#define DWORD int
#define WCHAR wchar_t
#define TCHAR char
#endif

namespace OperatingSystem{
    namespace Path{
        /// The character used by the operating system to separate pathname
        /// components. This is '/' for POSIX and '\\' for Windows.
        QString sep();

        /// Join two path components intelligently. The return value is the
        /// concatenation of path1, and path2, with exactly one directory separator.
        QString join(const QString& path1, const QString& path2);
    }

//    /// Show an error message to the user
//    void fehlermeldung(std::string Text, std::string Titel);
//    /// Show an error message to the user
//    void fehlermeldung(DWORD fehlernummer);

    /// Get the error message for a specified error
    ///
    /// \param fehlernummer The error ID
    QString errorMessage(DWORD errorid);

    namespace privat{
        // Max. Laenge der verwendeten C-Strings
        const size_t max_stringlaenge = 4096;

        // Aus einem String einen WCHAR-String machen
        void StringToWCHAR(const std::string& s, WCHAR ws[max_stringlaenge]);

        // Make a WCHAR-String out of a QString
        void QStringToWCHAR(const QString& s, WCHAR ws[max_stringlaenge]);

        std::string WCHARToString(WCHAR* ws);

        std::string TCHARToString(TCHAR* tc);

        void throwError(DWORD errorid);
    }

    // Returns the current working directory
    QString get_cd();

    // Returns the name of the running application.
    QString get_appname();

    // Returns the directory the running application is in.
    QString get_appdir();

    /// Get the current user's name and domain name (passed by reference!).
    /// Returns true on success.
    ///
    /// \param name The string to store the user name in
    /// \param domain The string to store the domain name in
    bool get_user(QString& name, QString& domain);

    // Returns the local user accounts.
    std::vector<QString> local_users();

    //Zwei Möglichkeiten ein Programm via Shellaufruf zu starten
    void programm_starten(const QString& sdateiname
                        , const QString& sparameter = ""
                        , const QString& spfad = ""
                        , bool unsichtbar = false);

    // Einen Prozess starten
    void prozess_starten( const QString& sdateiname
                        , const QString& sparameter = ""
                        , const QString& spfad = ""
                        , bool unsichtbar = "");

    // Einen Prozess unter anderem Benutzernamen starten
    bool prozess_starten_als(const QString& Benutzername, const QString& Domain, const QString& Passwort
                             ,const QString& dateiname, const QString& parameter, const QString& pfad);

    DECLARE_EXCEPTION(OSError);
}
#endif
