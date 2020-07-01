#ifndef TSUKI_EVENT_MOUSEWHEEL_H
#define TSUKI_EVENT_MOUSEWHEEL_H

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Event/EventBase.h>

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

    static bool push(int x, int y);

private:
    const SDL_MouseWheelEvent& m_Event;
};

}; // namespace Tsuki

#endif 