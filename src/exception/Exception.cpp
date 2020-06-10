#include <string>
#include <cstdarg>
#include <cstdio>
#include <Tsuki/Exception.hpp>

namespace Tsuki
{

Exception::Exception(const char* fmt, ...) : 
    m_Message(nullptr)
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

const char* Exception::what() const noexcept
{
    return m_Message.get();
}

}; //namespace Tsuki