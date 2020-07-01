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
    Exception(uint32_t code, const char* fmt, ...);
    virtual ~Exception() = default;

    virtual uint32_t code() const noexcept;
    virtual const char* what() const noexcept override;

    virtual void setUserData(const void* data) noexcept;
    virtual const void* userData() const noexcept;

private:
    uint32_t m_Code;
    std::shared_ptr<char> m_Message;
    const void* m_UserData;
};


#define TSUKI_DEFINE_ERROR(ERROR_NAME)  \
class ERROR_NAME : public Exception     \
{                                       \
public:                                 \
    template<typename... Types>         \
    ERROR_NAME(Types... args):          \
        Exception(args...)              \
    {}                                  \
    virtual ~ERROR_NAME() = default;    \
}

TSUKI_DEFINE_ERROR(NullError);
TSUKI_DEFINE_ERROR(FatalError);
TSUKI_DEFINE_ERROR(RuntimeError);


}; //namespace Tsuki

#endif