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

bool Event::MouseWheel::push(int x, int y)
{
    SDL_Event event;
    event.type = static_cast<uint32_t>(Event::Type::MouseWheel);
    event.wheel.x = x;
    event.wheel.y = y;
    int ret = SDL_PushEvent(&event);
    if(ret != 1)
    {
        throw RuntimeError("SDL_PushEvent(%p) : %s", &event, SDL_GetError());
    }
    return ret == 1;
}

}; // namespace Tsuki