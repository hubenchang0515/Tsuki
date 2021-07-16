#include <Tsuki/Event/Event.h>
#include <Tsuki/Core/Timer.h>

namespace Tsuki
{

std::map<void*, std::shared_ptr<void>> Event::m_Cache;

bool Event::hold(const std::shared_ptr<void>& ptr)
{
    auto pos = Event::m_Cache.find(ptr.get());
    if(pos == Event::m_Cache.end())
    {
        Event::m_Cache[ptr.get()] = ptr;
        return true;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<void> Event::unhold(void* ptr)
{
    if(ptr == nullptr)
    {
        return nullptr;
    }

    auto pos = Event::m_Cache.find(ptr);
    if(pos == Event::m_Cache.end())
    {
        return nullptr;
    }
    else
    {
        std::shared_ptr<void> sp = Event::m_Cache[ptr];
        Event::m_Cache.erase(ptr);
        return sp;
    }
}

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

void Event::setHandler(Event::Type type, std::function<void(void)> callback)
{
    m_Handlers[type] = [&callback](Event&){callback();};
}

void Event::setHandler(Event::Type type, std::function<void(Event&)> callback)
{
    m_Handlers[type] = callback;
}

void Event::dispatch()
{
    while(this->poll())
    {
        auto pair = m_Handlers.find(type());
        if(pair != m_Handlers.end())
        {
            pair->second(*this);
        }
        
        Type t = static_cast<Type>(m_Event.type);
        if(t > Type::__Tsuki && t < Type::User)
        {
            Event::unhold(m_Event.user.data1);
            Event::unhold(m_Event.user.data2);
        }
    }
}

} // namespace Tsuki 