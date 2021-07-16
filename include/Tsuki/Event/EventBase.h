#ifndef TSUKI_EVENT_BASE_H
#define TSUKI_EVENT_BASE_H

#include <SDL2/SDL.h>
#include <map>
#include <functional>
#include <Tsuki/Core/Basic.h>
#include <Tsuki/Exception/Exception.hpp>

namespace Tsuki
{

class Event
{
public:
    enum class Type
    {
        None = 0,
        Quit = SDL_QUIT,
        KeyDown = SDL_KEYDOWN,
        KeyUp = SDL_KEYUP,
        MouseButtonDown = SDL_MOUSEBUTTONDOWN,
        MouseButtonUp = SDL_MOUSEBUTTONUP,
        MouseMove = SDL_MOUSEMOTION,
        MouseWheel = SDL_MOUSEWHEEL,
        __Tsuki = SDL_USEREVENT,
        Timer,
        MessageBox,
        User,
    };

    Event() = default;
    ~Event() = default;

    /************************************************************************
     * @brief 在事件循环中保存一个事件数据的指针
     * @param[in] ptr 事件数据的指针
     * @return 是否成功，失败表示存在相同的指针
     * *********************************************************************/
    static bool hold(const std::shared_ptr<void>& ptr);

    /************************************************************************
     * @brief 读取一个保存在事件循环中事件数据的指针，并将其从事件循环中移除
     * @param[in] ptr 指针值
     * @return 事件数据的指针
     * *********************************************************************/
    static std::shared_ptr<void> unhold(void* ptr);

    /************************************************************************
     * @brief 创建一个事件数据指针，并将其保存到事件循环中
     * @param[in] T 事件数据的类型
     * @return 事件数据的指针
     * *********************************************************************/
    template<typename T>
    static std::shared_ptr<T> createEventData()
    {
        std::shared_ptr<T> sp = std::make_shared<T>();
        hold(sp);
        return sp;
    }

    bool poll();
    bool wait();
    bool push();

    Event::Type type() const;
    void setHandler(Event::Type type, std::function<void(void)> callback);
    void setHandler(Event::Type type, std::function<void(Event&)> callback);
    void dispatch();

    /* Adapters */
    class Quit;
    class Keyboard;
    class MouseButton;
    class MouseMove;
    class MouseWheel;
    class Timer;
    class MessageBox;
    class User;

private:
    SDL_Event m_Event;

    // 事件处理函数表
    std::map<Event::Type, std::function<void(Event&)>> m_Handlers;

    // 保存在事件循环中的事件数据指针
    static std::map<void*, std::shared_ptr<void>> m_Cache;
};

} // namespace Tsuki 

#endif // TSUKI_EVENT_H