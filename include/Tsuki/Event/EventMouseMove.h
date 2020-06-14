#ifndef TSUKI_EVENT_MOUSEMOVE_H
#define TSUKI_EVENT_MOUSEMOVE_H

#include "Event.h"

namespace Tsuki
{

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


}; // namespace Tsuki

#endif 