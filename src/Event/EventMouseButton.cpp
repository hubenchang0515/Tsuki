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

bool Event::MouseButton::push(Button button, State state, int x, int y, int clicks)
{
    SDL_Event event;
    if(state == State::Down)
        event.type = static_cast<uint32_t>(Event::Type::MouseButtonDown);
    else
        event.type = static_cast<uint32_t>(Event::Type::MouseButtonUp);

    event.button.button = static_cast<uint8_t>(button);
    event.button.x = x;
    event.button.y = y;
    event.button.clicks = clicks;
    int ret = SDL_PushEvent(&event);
    if(ret != 1)
    {
        throw RuntimeError("SDL_PushEvent(%p) : %s", &event, SDL_GetError());
    }
    return ret == 1;
}

bool Event::MouseButton::push(Button button, State state, const Point& p, int clicks)
{
    return Event::MouseButton::push(button, state, p.x, p.y, clicks);
}


}; // namespace Tsuki