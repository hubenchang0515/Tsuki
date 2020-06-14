#include <Tsuki/Event/EventUser.h>

namespace Tsuki
{

Event::User::Type Event::User::m_TypeCount = 0;

Event::User::User(const Event& event) :
    m_Event(event.m_Event.user)
{

}

void* Event::User::data1()
{
    return m_Event.data1;
}

void* Event::User::data2()
{
    return m_Event.data2;
}

Event::User::Type Event::User::registerType()
{
    return Event::User::m_TypeCount++;
}

bool Event::User::push(Type type, void* data1, void* data2)
{
    SDL_Event event;
    event.type = static_cast<uint32_t>(Event::Type::User);
    event.user.code = type;
    event.user.data1 = data1;
    event.user.data2 = data2;
    int ret = SDL_PushEvent(&event);
    if(ret != 1)
    {
        throw EventError("SDL_PushEvent(%p) : %s", &event, SDL_GetError());
    }
    return ret == 1;
}

}; // namespace Tsuki