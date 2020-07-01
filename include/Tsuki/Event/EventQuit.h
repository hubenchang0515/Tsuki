#ifndef TSUKI_EVENT_QUIT_H
#define TSUKI_EVENT_QUIT_H

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Event/EventBase.h>
#include <Tsuki/Window/Keyboard.h>

namespace Tsuki
{
    
class Event::Quit
{
public:
    Quit() = delete;
    ~Quit() = default;

    static bool push();

private: 
    const SDL_QuitEvent& m_Event;
};

}; // namespace Tsuki

#endif 