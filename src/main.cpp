
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
//#include <string>
#include <vector>
#include <iostream>

//#include <boost/test/included/prg_exec_monitor.hpp>
//int cpp_main(int argc, char* argv[])
int main(int argc, char* argv[])
{
    // Instantiate the QApplication instance to prepare some basic configurations
    QApplication app(argc, argv);

    try{
        // Loging in or starting main program?
        bool login = true;
        QString configFilename = OperatingSystem::Path::join(
            OperatingSystem::get_appdir(), "settings.xml");

        // Scan application arguments
        for(int i=1; i<argc; ++i)
        {
            if(QString(argv[i]) == QString("--nologin"))
            {
                login = false;
            }
            if(QString(argv[i]) == QString("--config"))
            {
                if(++i<argc)
                    configFilename = QString(argv[i]);
            }
        }

        if(login) // Start in login mode
        {
            // Read settings
            Settings s(configFilename);


            // Informations for application restart as different user
            QString Verz = OperatingSystem::get_appdir();
            QString Prog = OperatingSystem::get_appname();
            QString Param = "--nologin";

            // Show the dialog
            LoginDialog ad(s.user());
            ad.show();
            int returnCode = app.exec();

            // Did the user click on "ok"?
            while(ad.result() == QDialog::Accepted)
            {
                // Try to start the application as different user
                if(OperatingSystem::prozess_starten_als(ad.Name, ad.Domain, ad.Passw, Prog, Param, Verz))
//                if(OperatingSystem::prozess_starten_als(ad.Name, ad.Domain, ad.Passw, "IEXPLORE", "", "C:\\EigeneProgramme\\browsers\\IE401_NT"))
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
            // Read settings
            cDEBUG(("Read settings from " + configFilename).toLocal8Bit().constData());
            Settings s(configFilename);

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
    }catch(const Settings::FileIOError& ex){
        cDEBUG(ex.what());
        return -97;
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
    }
    return -99;
}
