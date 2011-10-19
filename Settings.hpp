#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Menulist.hpp"
#include "BaseException.hpp"

#include <string>

class Settings
{
public:
    /// Constructor which automatically loads settings from the standard location
    Settings();

    /// Constructor which takes a filename
    ///
    /// \param filename the file to load the settings from
    Settings(std::string filename);

    /// Save the settings to a given file
    ///
    /// \param filename the file to save the settings to
    void save(const std::string& filename);

    /// Get the main menu as it is saved in the settings
    Menulist* hauptmenue();

    /// Get the username saved in the settings
    const std::string& user();

    /// Exception used on problems opening or writing files
    DECLARE_EXCEPTION(FileIOError);

private:
    void parseSettings(const std::string& xml);

//    const static std::string dateiname;
    const std::string dateiname;
    Menulist* _hauptmenue;
    std::string _user;
};

#endif
