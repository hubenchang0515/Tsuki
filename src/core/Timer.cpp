#include <Tsuki/Timer.h>
#include <Tsuki/Event.h>
#include <Tsuki/Exception.hpp>
#include <string>

namespace Tsuki
{

Timer::Timer(const std::string& name) :
    m_TimerID(0),
    m_Name(name),
    m_Ticks(SDL_GetTicks())
{

}

void Timer::setInterval(uint32_t ms)
{
    m_Interval = ms;
}

void Timer::setUserdata(void* userdata)
{
    m_Userdata = userdata;
}

void Timer::launch()
{
    if(m_TimerID != 0)
    {
        throw TimerError("Tsuki::Timer %s is already launched.", m_Name.c_str());
        return;
    }
    m_TimerID = SDL_AddTimer(m_Interval, m_PushTimerEvent, static_cast<void*>(this));
}

void Timer::stop()
{
    if(m_TimerID == 0)
    {
        throw TimerError("Tsuki::Timer %s hasn't been launched.", m_Name.c_str());
        return;
    }
    SDL_RemoveTimer(m_TimerID);
    m_TimerID = 0;
}

uint32_t Timer::GetTicks()
{
    return SDL_GetTicks();
}

void Timer::delay(uint32_t ms)
{
    SDL_Delay(ms);
}

void Timer::delayFps(float fps)
{
    uint32_t t = GetTicks();
    uint32_t ms = 1000.0f / fps + 0.5f;
    
    if(ms + m_Ticks > t)
    {
        SDL_Delay(ms + m_Ticks - t);
        m_Ticks = GetTicks();
    }
    else
    {
        float realFps = 1000.0f/(t - m_Ticks);
        m_Ticks = GetTicks();
        throw TimerError("Timer::delayFps real FPS %f < %f", realFps, fps);
    }
}


uint32_t Timer::m_PushTimerEvent(uint32_t interval, void* self)
{
    SDL_Event event;
    event.type = static_cast<uint32_t>(Event::Type::Timer);
    event.user.data1 = self;
    event.user.data2 = reinterpret_cast<void*>(interval);
    SDL_PushEvent(&event);
    return interval;
}

}; // namespace Tsuki