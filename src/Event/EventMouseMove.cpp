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

bool Event::MouseMove::push(int x, int y, int deltaX, int deltaY, State state)
{
    SDL_Event event;
    event.type = static_cast<uint32_t>(Event::Type::MouseMove);
    event.motion.state = static_cast<uint8_t>(state);
    event.motion.x = x;
    event.motion.y = y;
    event.motion.xrel = deltaX;
    event.motion.yrel = deltaY;
    int ret = SDL_PushEvent(&event);
    if(ret != 1)
    {
        throw RuntimeError("SDL_PushEvent(%p) : %s", &event, SDL_GetError());
    }
    return ret == 1;
}

bool Event::MouseMove::push(const Point& p, int deltaX, int deltaY, State state)
{
    return Event::MouseMove::push(p.x, p.y, deltaX, deltaY, state);
}

}; // namespace Tsuki