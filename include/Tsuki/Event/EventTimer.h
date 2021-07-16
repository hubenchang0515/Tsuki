#ifndef TSUKI_EVENT_TIMER_H
#define TSUKI_EVENT_TIMER_H

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Event/EventBase.h>
#include <Tsuki/Core/Timer.h>

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
    uint32_t interval();
    Tsuki::Timer* timer();

private:
    const SDL_UserEvent& m_Event;
    std::shared_ptr<TimerEventData> m_Data;
};

}; // namespace Tsuki

#endif 