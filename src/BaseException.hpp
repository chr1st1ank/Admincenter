#ifndef BASEEXCEPTION_HPP
#define BASEEXCEPTION_HPP

#include <QString>
//#include <string>

class BaseException : public std::exception
{
    private:
        QString _short;
        QString _detailed;

    public:
        BaseException(const QString& short_description)
            : _short(short_description), _detailed()
        {}

        BaseException(const QString& short_description, const QString& detailed_description)
            : _short(short_description), _detailed(detailed_description)
        {}

        ~BaseException() throw()
        {}

        const char* what() const throw()
        {
            return _short.toLocal8Bit().constData();
        }

        const QString& shortDescription() const throw()
        {
            return _short;
        }

        const QString& detailedDescription() const throw()
        {
            return _detailed;
        }

        virtual QString name() const throw() = 0;
};

#define DECLARE_EXCEPTION(N)                            \
class N : public BaseException                          \
{                                                       \
    public:                                             \
        N(const QString& short_description) : BaseException(short_description)\
        {}                                              \
        N(const QString& short_description,const QString& detailed_description) \
            : BaseException(short_description,detailed_description)\
        {}                                              \
        ~N() throw()                                    \
        {}                                              \
        QString name() const throw()                \
        {                                               \
            return QString(#N);                     \
        }                                               \
}

#endif // BASEEXCEPTION_HPP
