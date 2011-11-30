#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QApplication>

class Application : private QApplication
{
    public:
        Application(int argc, char* argv[]);
        ~Application();
        static Application* instance();
        int run();
        void reloadConfiguration();
    protected:
    private:
        QString _configFilename;
        bool _loginMode;
        static Application* _instance;
};

#endif // APPLICATION_HPP
