#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QApplication>

class Application : private QApplication
{
    public:
        Application(int argc, char* argv[]);
        int run();
    protected:
    private:
        QString _configFilename;
        bool _loginMode;
};

#endif // APPLICATION_HPP
