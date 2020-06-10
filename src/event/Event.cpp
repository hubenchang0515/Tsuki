#include <Tsuki/Event.h>
#include <Tsuki/log.hpp>
#include <Tsuki/Timer.h>

namespace Tsuki
{

bool Event::poll()
{
    return SDL_PollEvent(&m_Event) == 1;
}

bool Event::wait()
{
    return SDL_WaitEvent(&m_Event) == 1;
}

Event::Type Event::type() const
{
    return static_cast<Event::Type>(m_Event.type);
}

void Event::setHandler(Event::Type type, std::function<void(Event&)> callback)
{
    m_Handlers[type] = callback;
}

void Event::solve()
{
    while(this->poll())
    {
        auto pair = m_Handlers.find(type());
        if(pair != m_Handlers.end())
        {
            pair->second(*this);
        }
    }
}

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

Event::MessageBox::MessageBox(const Event& event) :  
    m_Event(event.m_Event.user)
{

}

const std::string Event::MessageBox::name()
{
    char* str = static_cast<char*>(m_Event.data1);
    return str;
}

Event::MessageBox::Button Event::MessageBox::button()
{
    uint64_t buttonId = reinterpret_cast<uint64_t>(m_Event.data2);
    return static_cast<Event::MessageBox::Button>(buttonId);
}

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

} // namespace Tsuki 