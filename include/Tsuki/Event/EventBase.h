#ifndef TSUKI_EVENT_H
#define TSUKI_EVENT_H

#include <SDL2/SDL.h>
#include <map>
#include <functional>
#include "../Basic.h"
#include "../Keyboard.h"

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
    class Keyboard;
    class MouseButton;
    class MouseMove;
    class MouseWheel;
    class Timer;
    class MessageBox;

private:
    SDL_Event m_Event;
    std::map<Event::Type, std::function<void(Event&)> > m_Handlers;
};

} // namespace Tsuki 

#endif // TSUKI_EVENT_H