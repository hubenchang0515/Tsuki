#ifndef TSUKI_EVENT_TIMER_H
#define TSUKI_EVENT_TIMER_H

#include "EventBase.h"

namespace Tsuki
{

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

}; // namespace Tsuki

#endif 