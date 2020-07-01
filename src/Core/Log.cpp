#include <Tsuki/Core/Log.hpp>
#include <cstring>
#include <cerrno>
#include <thread>

namespace Tsuki
{

Log::Log() :
    m_Sync(false),
    m_Info(stdout),
    m_Error(stderr)
{

}

Log::~Log()
{
    if(m_Info != nullptr && m_Info != stdout)
    {
        fclose(m_Info);
        m_Info = nullptr;
    }

    if(m_Error != nullptr && m_Error != stderr)
    {
        fclose(m_Error);
        m_Error = nullptr;
    }
}

Log& Log::instance()
{
    static Log log;
    return log;
}

bool Log::redirectInfo(const char* file)
{
    FILE* fp = fopen(file, "ab+");
    if(fp == nullptr)
    {
        instance().error("redirectInfo(%s)", file);
        instance().error("%s", strerror(errno));
        return false;
    }

    m_Info = fp;
    return true;
}

bool Log::redirectInfo(FILE* fp)
{
    if(fp == nullptr)
    {
        instance().error("redirectInfo(%p)", fp);
        return false;
    }

    m_Info = fp;
    return true;
}

bool Log::redirectError(const char* file)
{
    FILE* fp = fopen(file, "ab+");
    if(fp == nullptr)
    {
        instance().error("redirectError(%s)", file);
        instance().error("%s", strerror(errno));
        return false;
    }

    m_Error = fp;
    return true;
}

bool Log::redirectError(FILE* fp)
{
    if(fp == nullptr)
    {
        instance().error("redirectError(%p)", fp);
        return false;
    }

    m_Error = fp;
    return true;
}

void Log::autoSync(bool sync)
{
    m_Sync = sync;
}

}  // namespace Tsuki