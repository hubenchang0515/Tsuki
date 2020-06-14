#include <Tsuki/MessageBox.h>
#include <Tsuki/Window.h>
#include <Tsuki/Event/EventMessageBox.h>

namespace Tsuki
{

MessageBox::MessageBox(const std::string& name) :
    m_Name(name)
{

}

void MessageBox::show(const std::string& title, const std::string& content, Type type)
{
    Thread th(m_ShowMessageBox, m_Name.c_str(), nullptr, title.c_str(), content.c_str(), type);
    th.detach(); 
}

MessageBox::Button MessageBox::show(const Window& window, const std::string& title, const std::string& content, Type type)
{
    return m_ShowMessageBox(m_Name.c_str(), window.getRaw(), title.c_str(), content.c_str(), type); 
}

MessageBox::Button MessageBox::m_ShowMessageBox(const char* name, SDL_Window* window, const char* title, const char* content, Type type)
{
    if(type < Type::Question)
    {
        SDL_ShowSimpleMessageBox(static_cast<uint32_t>(type), title, content, window);
        return MessageBox::Button::None;
    }
    else
    {
        static SDL_MessageBoxButtonData buttons[] = {
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, static_cast<int>(Button::Yes), "Yes" },
            { 0, static_cast<int>(Button::No), "No" },
            { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, static_cast<int>(Button::Cancel), "Cancel" },
        };

        static const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION,
            window,
            title,
            content,
            3, 
            buttons,
            nullptr
        };

        int buttonID;
        SDL_ShowMessageBox(&messageboxdata, &buttonID);

        SDL_Event event;
        event.type = static_cast<uint32_t>(Event::Type::MessageBox);
        event.user.data2 = const_cast<void*>(reinterpret_cast<const void*>(name));
        event.user.data1 = reinterpret_cast<void*>(buttonID);
        SDL_PushEvent(&event);
        return static_cast<MessageBox::Button>(buttonID);
    }
    
}

}; // namespace Tsuki