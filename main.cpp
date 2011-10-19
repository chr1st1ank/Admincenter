
#include "LoginDialog.hpp"
#include "MenuDialog.hpp"
#include "MenuPresenter.hpp"

#include "BaseException.hpp"
#include "OperatingSystem.hpp"
#include "Settings.hpp"
#include "debug.h"

#include <QApplication>
#include <QDebug>
#include <QString>
#include <string>
#include <vector>
#include <iostream>

//#include <boost/test/included/prg_exec_monitor.hpp>
//int cpp_main(int argc, char* argv[])
int main(int argc, char* argv[])
{
    // Instantiate the QApplication instance to prepare some basic configurations
    QApplication app(argc, argv);

//    try{
        // Loging in or starting main program?
        bool login = true;

        // Scan application arguments
        for(int i=1; i<argc; ++i)
        {
            if(std::string(argv[i]) == std::string("--nologin"))
            {
                login = false;
                break;
            }
        }

        if(login) // Start in login mode
        {
            // Read settings from the standard settings file
//            Settings s(Settings::dateiname);
            Settings s;


            // Informations for application restart as different user
            std::string Verz = OperatingSystem::get_appdir();
            std::string Prog = OperatingSystem::get_appname();
            std::string Param = "--nologin";

            // Show the dialog
            LoginDialog ad(s.user());
            ad.show();
            int returnCode = app.exec();

            // Did the user click on "ok"?
            while(ad.result() == QDialog::Accepted)
            {
                // Try to start the application as different user
                if(OperatingSystem::prozess_starten_als(ad.Name, ad.Domain, ad.Passw, Prog, Param, Verz))
                {
                    return returnCode;
                }
                // Failed, so try again
                ad.show();
                returnCode = app.exec();
            }

            // User tries to quit or succeeded starting child process -> exit
            return returnCode;
        }
        else //if(login) -> Start as main program
        {
            // Read settings from the standard settings file
            cDEBUG("Read settings from " << Settings::dateiname);
//            Settings s(Settings::dateiname);
            Settings s;

            // Create and show the top-level menu
            cDEBUG("Create menu");
            MenuPresenter* mp = MenuPresenter::instance();
            cDEBUG("Update menu");
            mp->updateList(s.hauptmenue());
            cDEBUG("Show menu");
            mp->showDialog();

            int returnCode = app.exec();

            cDEBUG("finished with retcode " << returnCode);
            return returnCode;
        }
//    }catch(const BaseException& ex){
//        cDEBUG(ex.name());
//        cDEBUG(ex.what());
//        return -96;
//    }catch(const std::exception& ex){
//        QDebug(ex.what());
//        return -97;
//    }catch(const std::string& s){
//        cDEBUG(s);
//        return -98;
//    }
    return -99;
}
