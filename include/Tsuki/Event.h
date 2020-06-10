#ifndef TSUKI_EVENT_H
#define TSUKI_EVENT_H

#include <SDL2/SDL.h>
#include <map>
#include <functional>
#include "basic.h"

namespace Tsuki
{

class Event
{
public:
    enum class Type
    {
        None = 0,
        Quit = SDL_QUIT,
        MouseButtonDown = SDL_MOUSEBUTTONDOWN,
        MouseButtonUp = SDL_MOUSEBUTTONUP,
        MouseMove = SDL_MOUSEMOTION,
        MouseWheel = SDL_MOUSEWHEEL,
        Timer = SDL_USEREVENT,
        MessageBox
    };

    Event() = default;
    ~Event() = default;

    bool poll();
    bool wait();

    Event::Type type() const;
    void setHandler(Event::Type type, std::function<void(Event&)> callback);
    void solve();

    /* Adapters */
    class MouseButton;
    class MouseMove;
    class MouseWheel;
    class Timer;
    class MessageBox;

private:
    SDL_Event m_Event;
    std::map<Event::Type, std::function<void(Event&)> > m_Handlers;
};

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

class Event::MouseMove
{
public:
    enum class State
    {
        Down = SDL_PRESSED,
        Up = SDL_RELEASED,
    };

    MouseMove() = delete;
    MouseMove(const Event& event);
    ~MouseMove() = default;

    State state() const;
    void point(Point& p) const;
    void point(int& x, int& y) const;
    void delta(int& deltaX, int& deltaY) const;

private:
    const SDL_MouseMotionEvent& m_Event;
};

class Event::MouseWheel
{
public:
    enum class Direction
    {
        Normal = SDL_MOUSEWHEEL_NORMAL,
        Flipped = SDL_MOUSEWHEEL_FLIPPED,
    };

    MouseWheel() = delete;
    MouseWheel(const Event& event);
    ~MouseWheel() = default;

    void distance(int& x, int& y) const;
    Direction direction() const;

private:
    const SDL_MouseWheelEvent& m_Event;
};

class Event::MessageBox
{
public:
    enum class Button
    {
        None = 0,
        Yes,
        No,
        Cancel,
    };

    MessageBox() = delete;
    MessageBox(const Event& event);
    ~MessageBox() = default;

    const std::string name();
    Button button();

private:
    const SDL_UserEvent& m_Event;
};

class Timer;

class Event::Timer
{
public:
    Timer() = delete;
    Timer(const Event& event);
    ~Timer() = default;

    const std::string name();
    Tsuki::Timer& timer();

private:
    const SDL_UserEvent& m_Event;
};

} // namespace Tsuki 

#endif // TSUKI_EVENT_H