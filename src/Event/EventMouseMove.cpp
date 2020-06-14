#include <Tsuki/Event/EventMouseMove.h>

namespace Tsuki
{

Event::MouseMove::MouseMove(const Event& event) :  
    m_Event(event.m_Event.motion)
{

}

Event::MouseMove::State Event::MouseMove::state() const
{
    return static_cast<Event::MouseMove::State>(m_Event.state);
}

void Event::MouseMove::point(Point& point) const
{
    point.x = m_Event.x;
    point.y = m_Event.y;
}

void Event::MouseMove::point(int& x, int& y) const
{
    x = m_Event.x;
    y = m_Event.y;
}

void Event::MouseMove::delta(int& deltaX, int& deltaY) const
{
    deltaX = m_Event.xrel;
    deltaY = m_Event.yrel;
}

}; // namespace Tsuki