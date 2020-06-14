#ifndef TSUKI_EXCEPTION_H
#define TSUKI_EXCEPTION_H

#include <string>
#include <stdexcept>
#include <memory>
#include <cstdarg>

namespace Tsuki
{

class Exception : public std::exception
{
public:
    Exception(const char* fmt, ...);
    virtual ~Exception() = default;

    virtual const char* what() const noexcept override;

private:
    std::shared_ptr<char> m_Message;
};

class NullError : public Exception
{
public:
    template<typename... Types>
    NullError(Types... args):
        Exception(args...)
    {

    }

    virtual ~NullError() = default;
};

class MemoryError : public Exception
{
public:
    template<typename... Types>
    MemoryError(Types... args):
        Exception(args...)
    {

    }

    virtual ~MemoryError() = default;
};

class ObjectCreateError : public Exception
{
public:
    template<typename... Types>
    ObjectCreateError(Types... args):
        Exception(args...)
    {

    }

    virtual ~ObjectCreateError() = default;
};

class RenderError : public Exception
{
public:
    template<typename... Types>
    RenderError(Types... args):
        Exception(args...)
    {

    }

    virtual ~RenderError() = default;
};

class IOError : public Exception
{
public:
    template<typename... Types>
    IOError(Types... args):
        Exception(args...)
    {

    }

    virtual ~IOError() = default;
};

class ThreadError : public Exception
{
public:
    template<typename... Types>
    ThreadError(Types... args):
        Exception(args...)
    {

    }

    virtual ~ThreadError() = default;
};

class TimerError : public Exception
{
public:
    template<typename... Types>
    TimerError(Types... args):
        Exception(args...)
    {

    }

    virtual ~TimerError() = default;
};

class EventError : public Exception
{
public:
    template<typename... Types>
    EventError(Types... args):
        Exception(args...)
    {

    }

    virtual ~EventError() = default;
};

}; //namespace Tsuki

#endif