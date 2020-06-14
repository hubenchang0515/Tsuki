#include <Tsuki/Event/EventKeyboard.h>
#include <Tsuki/Keyboard.h>

namespace Tsuki
{

Event::Keyboard::Keyboard(const Event& event):
    m_Event(event.m_Event.key)
{

}

Tsuki::Keyboard::KeyCode Event::Keyboard::keyCode()
{
    return m_Event.keysym.sym;
}

Tsuki::Keyboard::ScanCode Event::Keyboard::scanCode()
{
    return m_Event.keysym.scancode;
}

Event::Keyboard::State Event::Keyboard::state() const
{
    return static_cast<Event::Keyboard::State>(m_Event.state);
}

}; // namespace Tsuki