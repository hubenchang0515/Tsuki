#ifndef TSUKI_EVENT_KEYBOARD_H
#define TSUKI_EVENT_KEYBOARD_H

#include "Event.h"

namespace Tsuki
{
    
class Event::Keyboard
{
public:
    enum class State
    {
        Down = SDL_PRESSED,
        Up = SDL_RELEASED,
    };

    Keyboard() = delete;
    Keyboard(const Event& event);
    ~Keyboard() = default;

    Tsuki::Keyboard::KeyCode keyCode();
    Tsuki::Keyboard::ScanCode scanCode();

    State state() const;

private: 
    const SDL_KeyboardEvent& m_Event;
};

}; // namespace Tsuki

#endif 