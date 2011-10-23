#ifndef BASEEXCEPTION_HPP
#define BASEEXCEPTION_HPP

#include <QString>
//#include <string>

class BaseException : public std::exception
{
    private:
        QString _what;

    public:
        BaseException(const QString& what)
            : _what(what)
        {}

        ~BaseException() throw()
        {}

        const char* what() const throw()
        {
            return _what.toLocal8Bit().constData();
        }

        const QString& what_string() const throw()
        {
            return _what;
        }

        virtual QString name() const throw() = 0;
};

#define DECLARE_EXCEPTION(N)                            \
class N : public BaseException                          \
{                                                       \
    public:                                             \
        N(const QString& what) : BaseException(what)\
        {}                                              \
        ~N() throw()                                    \
        {}                                              \
        QString name() const throw()                \
        {                                               \
            return QString(#N);                     \
        }                                               \
}

#endif // BASEEXCEPTION_HPP
