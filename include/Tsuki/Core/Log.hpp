#ifndef TSUKI_LOG_H
#define TSUKI_LOG_H

#include <cstdio>

namespace Tsuki
{

class Log
{
public:
    Log();
    ~Log();

    static Log& instance();

    bool redirectInfo(const char* file);
    bool redirectInfo(FILE* fp);
    bool redirectError(const char* file);
    bool redirectError(FILE* fp);
    void autoSync(bool sync);


    template<typename... Types>
    void info(Types... args)
    {
        fprintf(m_Info, "INFO: ");
        fprintf(m_Info, args...);
        fprintf(m_Info, "\n");
        if(m_Sync)
            fflush(m_Info);
    }

    template<typename... Types>
    void error(Types... args)
    {
        fprintf(m_Error, "ERROR: ");
        fprintf(m_Error, args...);
        fprintf(m_Error, "\n");
        if(m_Sync)
            fflush(m_Error);
    }


private:
    bool m_Sync;
    FILE* m_Info;
    FILE* m_Error;
};

#ifndef TsukiLog
#define TsukiLog (::Tsuki::Log::instance())
#endif

} // namespace Tsuki

#endif