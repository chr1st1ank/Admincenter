#ifndef BASEEXCEPTION_HPP
#define BASEEXCEPTION_HPP

//#include <string>

class BaseException : public std::exception
{
    private:
        std::string _what;

    public:
        BaseException(const std::string& what)
            : _what(what)
        {}

        ~BaseException() throw()
        {}

        const char* what() const throw()
        {
            return _what.c_str();
        }

        const std::string& what_string() const throw()
        {
            return _what;
        }

        virtual std::string name() const throw() = 0;
};

#define DECLARE_EXCEPTION(N)                            \
class N : public BaseException                          \
{                                                       \
    public:                                             \
        N(const std::string& what) : BaseException(what)\
        {}                                              \
        ~N() throw()                                    \
        {}                                              \
        std::string name() const throw()                \
        {                                               \
            return std::string(#N);                     \
        }                                               \
}

#endif // BASEEXCEPTION_HPP
