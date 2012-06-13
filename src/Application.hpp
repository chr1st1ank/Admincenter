#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Settings.hpp"
#include <QApplication>

class Application : private QApplication
{
    public:
        Application(int argc, char* argv[]);
        ~Application();
        static Application* instance();
        int run();
        void reloadConfiguration();
        const Settings& settings() const;
        QString configFilename() const;
    protected:
    private:
        QString _configFilename;
        Settings* _settings;
        bool _loginMode;
        static Application* _instance;
};

#endif // APPLICATION_HPP
