#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Menulist.hpp"
#include "BaseException.hpp"

#include <string>
#include <QString>
#include <QDebug>

class Settings
{
public:
    /// Constructor which takes a filename to load the settings from
    ///
    /// \param filename the file to load the settings from
    Settings(QString filename);

    ~Settings() {qDebug() << "Deleting Settings";};

    /// Save the settings to a given file
    ///
    /// \param filename the file to save the settings to
//    void save(const QString& filename);

    /// Get the main menu as it is saved in the settings
    Menulist* hauptmenue();

    /// Get the default username saved in the settings
    const QString& user() const;

    /// Get the path of the default text editor saved in the settings
    const QString& textEditor() const;

    /// Exception used on problems opening or writing files
    DECLARE_EXCEPTION(FileIOError);

private:
    /// Load settings from a string containing correct XML
    ///
    /// \param A std::string containing the settings as xml
    void parseSettings(const std::string& xml);

    Menulist* _hauptmenue;
    QString _user;
    QString _textEditor;
};

#endif
