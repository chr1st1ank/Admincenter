#include "Application.hpp"

#include "LoginDialog.hpp"
#include "MenuDialog.hpp"
#include "MenuPresenter.hpp"

#include "BaseException.hpp"
#include "OperatingSystem.hpp"
#include "Settings.hpp"
#include "debug.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>

Application::Application(int argc, char* argv[]) : QApplication(argc, argv)
{
    // Loging in or starting main program?
    _loginMode = true;
    _configFilename = OperatingSystem::Path::join(OperatingSystem::get_appdir(), "settings.xml");

    // Scan application arguments
    for(int i=1; i<argc; ++i)
    {
        if(QString(argv[i]) == QString("--nologin"))
        {
            _loginMode = false;
        }
        if(QString(argv[i]) == QString("--config"))
        {
            if(++i<argc)
                _configFilename = QString(argv[i]);
        }
    }
}

int Application::run()
{
    try{
        if(_loginMode) // Start in login mode
        {
            // Read settings
            Settings s(_configFilename);

            // Show the dialog
            LoginDialog ad(s.user());
            ad.show();
            int returnCode = exec();

            // Did the user click on "ok"?
            while(ad.result() == QDialog::Accepted)
            {
                // Try to start the application as different user
                try{
                    if(OperatingSystem::prozess_starten_als(
                        ad.Name, ad.Domain, ad.Passw, OperatingSystem::get_appname(),
                        "--nologin", OperatingSystem::get_appdir())
                       )
                    {
                        return returnCode;
                    }
                }catch(const OperatingSystem::OSError& err){
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(QObject::tr("Error Starting Main Process"));
                    msgBox.setText(err.shortDescription());
                    msgBox.setInformativeText(err.detailedDescription());
//                    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//                    msgBox.setDefaultButton(QMessageBox::Save);
                    msgBox.exec();
                }
                // Failed, so try again
                ad.show();
                returnCode = exec();
            }

            // User tries to quit or succeeded starting child process -> exit
            return returnCode;
        }
        else //if(_loginMode) -> Start as main program
        {
            // Create and show the top-level menu
            cDEBUG("Create menu");
            MenuPresenter* mp = MenuPresenter::instance();

            int returnCode = 0;
            do
            {
                // Read settings
                cDEBUG(("Read settings from " + _configFilename).toLocal8Bit().constData());
                Settings s(_configFilename);

                // Prepare and run the dialog
                cDEBUG("Update menu");
                mp->updateList(s.hauptmenue());
                cDEBUG("Show menu");
                mp->showDialog();

                returnCode = exec();
            }while(mp->status() == MenuPresenter::exitStatusRestart);

            cDEBUG("finished with retcode " << returnCode);
            return returnCode;
        }
    }catch(const Settings::FileIOError& ex){
        cDEBUG(ex.what());
        return -97;
    }
    return -99;
}
