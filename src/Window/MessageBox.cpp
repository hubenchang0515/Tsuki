#include <Tsuki/Window/MessageBox.h>
#include <Tsuki/Window/Window.h>
#include <Tsuki/Event/EventMessageBox.h>
#include <Tsuki/Core/Log.hpp>

namespace Tsuki
{

MessageBox::MessageBox(const std::string& name) noexcept:
    m_Name(name)
{

}

void MessageBox::show(const std::string& title, const std::string& content, Type type)
{
    Thread th(m_ShowMessageBox, m_Name, nullptr, title, content, type);
    th.detach(); 
}

MessageBox::Button MessageBox::show(const Window* window, const std::string& title, const std::string& content, Type type)
{
    return m_ShowMessageBox(m_Name, window->getRaw(), title, content, type); 
}

MessageBox::Button MessageBox::m_ShowMessageBox(const std::string& name, SDL_Window* window, const std::string& title, const std::string& content, Type type)
{
    if(type < Type::Question)
    {
        SDL_ShowSimpleMessageBox(static_cast<uint32_t>(type), title.c_str(), content.c_str(), window);
        return MessageBox::Button::None;
    }
    else
    {
        static SDL_MessageBoxButtonData buttons[] = {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(Button::Yes), "Yes" },
            { 0, static_cast<int>(Button::No), "No" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(Button::Cancel), "Cancel" },
        };

        const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION,
            window,
            title.c_str(),
            content.c_str(),
            3, 
            buttons,
            nullptr
        };

        int buttonID;
        SDL_ShowMessageBox(&messageboxdata, &buttonID);

        SDL_Event event;
        event.type = static_cast<uint32_t>(Event::Type::MessageBox);
        event.user.data1 = const_cast<void*>(reinterpret_cast<const void*>(&name));
        event.user.data2 = reinterpret_cast<void*>(buttonID);
        SDL_PushEvent(&event);
        return static_cast<MessageBox::Button>(buttonID);
    }
    
}

}; // namespace Tsuki