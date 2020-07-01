#include <Tsuki/Event/Event.h>
#include <Tsuki/Core/Timer.h>

namespace Tsuki
{

bool Event::poll()
{
    return SDL_PollEvent(&m_Event) == 1;
}

bool Event::wait()
{
    return SDL_WaitEvent(&m_Event) == 1;
}

bool Event::push()
{
    return SDL_PushEvent(&m_Event) == 1;
}

Event::Type Event::type() const
{
    return static_cast<Event::Type>(m_Event.type);
}

void Event::setHandler(Event::Type type, std::function<void(Event&)> callback)
{
    m_Handlers[type] = callback;
}

void Event::solve()
{
    while(this->poll())
    {
        auto pair = m_Handlers.find(type());
        if(pair != m_Handlers.end())
        {
            pair->second(*this);
        }
    }
}

} // namespace Tsuki 