#ifndef TSUKI_EVENT_BASE_H
#define TSUKI_EVENT_BASE_H

#include <SDL2/SDL.h>
#include <map>
#include <functional>
#include <Tsuki/Core/Basic.h>
#include <Tsuki/Exception/Exception.hpp>

namespace Tsuki
{

class Event
{
public:
    enum class Type
    {
        None = 0,
        Quit = SDL_QUIT,
        KeyDown = SDL_KEYDOWN,
        KeyUp = SDL_KEYUP,
        MouseButtonDown = SDL_MOUSEBUTTONDOWN,
        MouseButtonUp = SDL_MOUSEBUTTONUP,
        MouseMove = SDL_MOUSEMOTION,
        MouseWheel = SDL_MOUSEWHEEL,
        Timer = SDL_USEREVENT,
        MessageBox,
        User,
    };

    Event() = default;
    ~Event() = default;

    bool poll();
    bool wait();
    bool push();

    Event::Type type() const;
    void setHandler(Event::Type type, std::function<void(void)> callback);
    void setHandler(Event::Type type, std::function<void(Event&)> callback);
    void dispatch();

    /* Adapters */
    class Quit;
    class Keyboard;
    class MouseButton;
    class MouseMove;
    class MouseWheel;
    class Timer;
    class MessageBox;
    class User;

private:
    SDL_Event m_Event;
    std::map<Event::Type, std::function<void(Event&)> > m_Handlers;
};

} // namespace Tsuki 

#endif // TSUKI_EVENT_H