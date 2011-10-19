#ifndef OPERATINGSYSTEM_HPP
#define OPERATINGSYSTEM_HPP

#include <string>
#include <vector>

#ifdef _WIN32
#define WINVER 0x0500
#include <windows.h>
#else
#define DWORD int
#define WCHAR std::string
#endif

namespace OperatingSystem{

    void fehlermeldung(std::string Text, std::string Titel);
    void fehlermeldung(DWORD fehlernummer);
    std::string fehlertext(DWORD fehlernummer);

    namespace privat{
        // Max. Laenge der verwendeten C-Strings
        const size_t max_stringlaenge = 4096;

        // Aus einem String einen WCHAR-String machen
        void StringToWCHAR(const std::string& s, WCHAR ws[max_stringlaenge]);

        std::string WCHARToString(WCHAR* ws);

        std::string TCHARToString(TCHAR* tc);
    }

    // Aktuelles Arbeitsverzeichnis angeben
    std::string get_cd();

    // Name der laufenden Anwendung
    std::string get_appname();

    // Verzeichnis in welchem sich die laufende Anwendung befindet
    std::string get_appdir();

    //Anzeigen von Nutzer und Domain
    bool get_user(std::string& Name, std::string& Domain);

    // Rückgabe der lokalen Benutzerkonten
    std::vector<std::string> lokale_benutzer();

    //Zwei Möglichkeiten ein Programm via Shellaufruf zu starten
    void programm_starten(const std::string& sdateiname
                        , const std::string& sparameter = ""
                        , const std::string& spfad = ""
                        , bool unsichtbar = false);

    // Einen Prozess starten
    void prozess_starten( const std::string& sdateiname
                        , const std::string& sparameter = ""
                        , const std::string& spfad = ""
                        , bool unsichtbar = "");

    // Einen Prozess unter anderem Benutzernamen starten
    bool prozess_starten_als(const std::string& Benutzername, const std::string& Domain, const std::string& Passwort
                             ,const std::string& dateiname, const std::string& parameter, const std::string& pfad);

}
#endif
