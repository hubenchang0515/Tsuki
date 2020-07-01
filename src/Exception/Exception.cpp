#include <string>
#include <cstdarg>
#include <cstdio>
#include <Tsuki/Exception/Exception.hpp>

namespace Tsuki
{

Exception::Exception(const char* fmt, ...) : 
    m_Message(nullptr),
    m_UserData(nullptr)
{
    va_list args;
    va_start(args, fmt);
    size_t len = vsnprintf(nullptr, 0, fmt, args) + 1;
    va_end(args);

    va_start(args, fmt);
    m_Message = std::shared_ptr<char>(new char[len], [](char* p){ delete[] p; });
    vsnprintf(m_Message.get(), len, fmt, args);
    va_end(args);
}

Exception::Exception(uint32_t code, const char* fmt, ...) : 
    m_Code(code),
    m_Message(nullptr),
    m_UserData(nullptr)
{
    va_list args;
    va_start(args, fmt);

    size_t len = vsnprintf(nullptr, 0, fmt, args) + 1;
    va_end(args);
    va_start(args, fmt);
    
    m_Message = std::shared_ptr<char>(new char[len], [](char* p){ delete[] p; });
    vsnprintf(m_Message.get(), len, fmt, args);

    va_end(args);
}

uint32_t Exception::code() const noexcept
{
    return m_Code;
}

const char* Exception::what() const noexcept
{
    return m_Message.get();
}

void Exception::setUserData(const void* data) noexcept
{
    m_UserData = data;
}

const void* Exception::userData() const noexcept
{
    return m_UserData;
}


}; //namespace Tsuki