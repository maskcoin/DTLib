#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "object.h"

namespace DTLib
{
#define THROW_EXCEPTION(e, m)  (throw e(m, __FILE__, __LINE__))

class Exception : public Object
{
protected:
    char* m_message;
    char* m_location;

    void init(const char* message, const char* file, int line);
public:
    Exception();
    Exception(const char* message);
    Exception(const char* file, int line);
    Exception(const char* message, const char* file, int line);

    Exception(const Exception& e);
    Exception& operator=(const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception() = 0;
};

class ArithmeticException : public Exception
{
public:
    ArithmeticException() : Exception() { }
    ArithmeticException(const char* message) : Exception(message) { }
    ArithmeticException(const char* file, int line) : Exception(file, line) { }
    ArithmeticException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    ArithmeticException(const ArithmeticException& e) : Exception(e) { }
    ArithmeticException& operator=(const ArithmeticException& e)
    {
        Exception::operator=(e);

        return *this;
    }
    ~ArithmeticException() {}
};

class PointerException : public Exception
{
public:
    PointerException() : Exception() { }
    PointerException(const char* message) : Exception(message) { }
    PointerException(const char* file, int line) : Exception(file, line) { }
    PointerException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    PointerException(const PointerException& e) : Exception(e) { }
    PointerException& operator=(const PointerException& e)
    {
        Exception::operator=(e);

        return *this;
    }
};

class IndexOutOfBoundsException : public Exception
{
public:
    IndexOutOfBoundsException() : Exception() { }
    IndexOutOfBoundsException(const char* message) : Exception(message) { }
    IndexOutOfBoundsException(const char* file, int line) : Exception(file, line) { }
    IndexOutOfBoundsException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) { }
    IndexOutOfBoundsException& operator=(const IndexOutOfBoundsException& e)
    {
        Exception::operator=(e);

        return *this;
    }
};

class NoEnoughMemoryException : public Exception
{
public:
    NoEnoughMemoryException() : Exception() { }
    NoEnoughMemoryException(const char* message) : Exception(message) { }
    NoEnoughMemoryException(const char* file, int line) : Exception(file, line) { }
    NoEnoughMemoryException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    NoEnoughMemoryException(const NoEnoughMemoryException& e) : Exception(e) { }
    NoEnoughMemoryException& operator=(const NoEnoughMemoryException& e)
    {
        Exception::operator=(e);

        return *this;
    }
};

class InvalidParameterException : public Exception
{
public:
    InvalidParameterException() : Exception() { }
    InvalidParameterException(const char* message) : Exception(message) { }
    InvalidParameterException(const char* file, int line) : Exception(file, line) { }
    InvalidParameterException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    InvalidParameterException(const InvalidParameterException& e) : Exception(e) { }
    InvalidParameterException& operator=(const InvalidParameterException& e)
    {
        Exception::operator=(e);

        return *this;
    }
};

class InvalidOperationException : public Exception
{
public:
    InvalidOperationException() : Exception() { }
    InvalidOperationException(const char* message) : Exception(message) { }
    InvalidOperationException(const char* file, int line) : Exception(file, line) { }
    InvalidOperationException(const char* message, const char* file, int line) : Exception(message, file, line) { }

    InvalidOperationException(const InvalidOperationException& e) : Exception(e) { }
    InvalidOperationException& operator=(const InvalidOperationException& e)
    {
        Exception::operator=(e);

        return *this;
    }
};
}


#endif // EXCEPTION_H
