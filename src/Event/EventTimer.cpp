#include <Tsuki/Event/EventTimer.h>

namespace Tsuki
{

Event::Timer::Timer(const Event& event) :  
    m_Event(event.m_Event.user)
{

}

const std::string Event::Timer::name()
{
    char* str = static_cast<char*>(m_Event.data1);
    return str;
}

Tsuki::Timer& Event::Timer::timer()
{
    return *static_cast<Tsuki::Timer*>(m_Event.data1);
}

}; // namespace Tsuki