#include <Tsuki/Event/EventMouseWheel.h>

namespace Tsuki
{

Event::MouseWheel::MouseWheel(const Event& event) :  
    m_Event(event.m_Event.wheel)
{

}

void Event::MouseWheel::distance(int& x, int& y) const
{
    x = m_Event.x;
    y = m_Event.y;
}

Event::MouseWheel::Direction Event::MouseWheel::direction() const
{
    return static_cast<Event::MouseWheel::Direction>(m_Event.direction);
}

}; // namespace Tsuki