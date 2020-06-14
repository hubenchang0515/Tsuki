#ifndef TSUKI_EVENT_MOUSEWHEEL_H
#define TSUKI_EVENT_MOUSEWHEEL_H

#include "Event.h"

namespace Tsuki
{

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

}; // namespace Tsuki

#endif 