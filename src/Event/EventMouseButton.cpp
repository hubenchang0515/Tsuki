#include <Tsuki/Event/EventMouseButton.h>

namespace Tsuki
{

Event::MouseButton::MouseButton(const Event& event):
    m_Event(event.m_Event.button)
{

}

Event::MouseButton::Button Event::MouseButton::button() const
{
    return static_cast<Event::MouseButton::Button>(m_Event.button);
}

Event::MouseButton::State Event::MouseButton::state() const
{
    return static_cast<Event::MouseButton::State>(m_Event.state);
}

int Event::MouseButton::clicks() const
{
    return m_Event.clicks;
}

void Event::MouseButton::point(Point& p) const
{
    p.x = m_Event.x;
    p.y = m_Event.y;
}

void Event::MouseButton::point(int& x, int& y) const
{
    x = m_Event.x;
    y = m_Event.y;
}


}; // namespace Tsuki