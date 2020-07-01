#ifndef TSUKI_EVENT_MOUSEMOVE_H
#define TSUKI_EVENT_MOUSEMOVE_H

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Event/EventBase.h>

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

    static bool push(int x, int y, int deltaX, int deltaY, State state=State::Up);
    static bool push(const Point& p, int deltaX, int deltaY, State state=State::Up);

private:
    const SDL_MouseMotionEvent& m_Event;
};


}; // namespace Tsuki

#endif 