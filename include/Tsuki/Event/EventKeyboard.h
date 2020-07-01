#ifndef TSUKI_EVENT_KEYBOARD_H
#define TSUKI_EVENT_KEYBOARD_H

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Event/EventBase.h>
#include <Tsuki/Window/Keyboard.h>

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
    using KeyCode = Tsuki::Keyboard::KeyCode;
    using ScanCode = Tsuki::Keyboard::ScanCode;

    Keyboard() = delete;
    Keyboard(const Event& event);
    ~Keyboard() = default;

    KeyCode keyCode();
    ScanCode scanCode();
    State state() const;

    static bool push(KeyCode keyCode, State state);
    static bool push(ScanCode scanCode, State state);

private: 
    const SDL_KeyboardEvent& m_Event;
};

}; // namespace Tsuki

#endif 