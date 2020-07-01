#ifndef TSUKI_EVENT_USER_H
#define TSUKI_EVENT_USER_H

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Event/EventBase.h>

namespace Tsuki
{
    
class Event::User
{
public:
    using Type = int32_t;

    User() = delete;
    User(const Event& event);
    ~User() = default;

    void* data1();
    void* data2();

    static Type registerType();
    static bool push(Type type, void* data1=nullptr, void* data2=nullptr);

private: 
    const SDL_UserEvent& m_Event;
    static Type m_TypeCount;
};

}; // namespace Tsuki

#endif 