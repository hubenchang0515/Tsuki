#include <Tsuki/Event/EventTimer.h>

namespace Tsuki
{

Event::Timer::Timer(const Event& event) :  
    m_Event(event.m_Event.user)
{
    auto sp = Event::unhold(event.m_Event.user.data1);
    m_Data = std::static_pointer_cast<TimerEventData>(sp);
}

const std::string Event::Timer::name()
{
    if(m_Data == nullptr)
    {
        return "";
    }
    return m_Data->name;
}

uint32_t Event::Timer::interval()
{
    if(m_Data == nullptr)
    {
        return 0;
    }
    return m_Data->interval;
}

Tsuki::Timer* Event::Timer::timer()
{
    return m_Data->timer;
}

}; // namespace Tsuki