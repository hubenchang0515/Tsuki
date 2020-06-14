#ifndef TSUKI_EVENT_MOUSEBUTTON_H
#define TSUKI_EVENT_MOUSEBUTTON_H

#include "Event.h"

namespace Tsuki
{

class Event::MouseButton
{
public:
    enum class Button
    {
        Left = SDL_BUTTON_LEFT,
        Middle = SDL_BUTTON_MIDDLE,
        Right = SDL_BUTTON_RIGHT,
    };

    enum class State
    {
        Down = SDL_PRESSED,
        Up = SDL_RELEASED,
    };

    MouseButton() = delete;
    MouseButton(const Event& event);
    ~MouseButton() = default;

    Button button() const;
    State state() const;
    int clicks() const;
    void point(Point& p) const;
    void point(int& x, int& y) const;

private: 
    const SDL_MouseButtonEvent& m_Event;
};

}; // namespace Tsuki

#endif 