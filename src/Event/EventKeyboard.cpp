#include <Tsuki/Event/EventKeyboard.h>

namespace Tsuki
{

Event::Keyboard::Keyboard(const Event& event):
    m_Event(event.m_Event.key)
{

}

Event::Keyboard::KeyCode Event::Keyboard::keyCode()
{
    return m_Event.keysym.sym;
}

Event::Keyboard::ScanCode Event::Keyboard::scanCode()
{
    return m_Event.keysym.scancode;
}

Event::Keyboard::State Event::Keyboard::state() const
{
    return static_cast<Event::Keyboard::State>(m_Event.state);
}

bool Event::Keyboard::push(KeyCode keyCode, State state)
{
    SDL_Event event;
    if(state == State::Down)
        event.type = SDL_KEYDOWN;
    else
        event.type = SDL_KEYUP;

    event.key.state = static_cast<uint8_t>(state);
    event.key.keysym.scancode = Tsuki::Keyboard::scanCode(keyCode);
    event.key.keysym.sym = keyCode;
    int ret = SDL_PushEvent(&event);
    if(ret != 1)
    {
        throw EventError("SDL_PushEvent(%p) : %s", &event, SDL_GetError());
    }
    return ret == 1;
}

bool Event::Keyboard::push(ScanCode scanCode, State state)
{
    SDL_Event event;
    if(state == State::Down)
        event.type = static_cast<uint32_t>(Event::Type::KeyDown);
    else
        event.type = static_cast<uint32_t>(Event::Type::KeyUp);

    event.key.state = static_cast<uint8_t>(state);
    event.key.keysym.scancode = scanCode;
    event.key.keysym.sym = Tsuki::Keyboard::keyCode(scanCode);
    int ret = SDL_PushEvent(&event);
    if(ret != 1)
    {
        throw EventError("SDL_PushEvent(%p) : %s", &event, SDL_GetError());
    }
    return ret == 1;
}

}; // namespace Tsuki