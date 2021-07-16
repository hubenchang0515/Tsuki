#ifndef TSUKI_TIMER_H
#define TSUKI_TIMER_H

#include <Tsuki/Core/Basic.h>
#include <string>
#include <Tsuki/Exception/Exception.hpp>

namespace Tsuki
{

class Timer;

struct TimerEventData
{
    std::string name;
    uint32_t interval;
    Timer* timer;
};

class Timer
{
public:
    Timer(const std::string& name);
    void setInterval(uint32_t ms);
    void setUserdata(void* userdata);
    void start();
    void stop();

    static uint32_t GetTicks();
    static void delay(uint32_t ms);
    float delayFps(float fps);


private:
    SDL_TimerID m_TimerID;
    std::string m_Name;
    uint32_t m_Ticks;

    uint32_t m_Interval;
    void* m_Userdata;

    static uint32_t m_PushTimerEvent(uint32_t interval, void* self);
};

}; // namespace Tsuki


#endif