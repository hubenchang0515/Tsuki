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
    auto data = Event::createEventData<MessageBoxEventData>();
    data->name = m_Name;
    data->title = title;
    data->content = content;
    Thread th(m_ShowMessageBox, nullptr, data, type);
    th.detach();
}

MessageBox::Button MessageBox::show(const Window* window, const std::string& title, const std::string& content, Type type)
{
    auto data = Event::createEventData<MessageBoxEventData>();
    data->name = m_Name;
    data->name = m_Name;
    data->title = title;
    data->content = content;
    return m_ShowMessageBox(window->getRaw(), data, type); 
}

MessageBox::Button MessageBox::m_ShowMessageBox(SDL_Window* window, std::shared_ptr<MessageBoxEventData> data, Type type)
{
    std::unique_ptr<char> title(strdup(data->title.c_str()));
    std::unique_ptr<char> content(strdup(data->content.c_str()));

    if(type < Type::Question)
    {
        SDL_ShowSimpleMessageBox(static_cast<uint32_t>(type), title.get(), content.get(), window);
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
            title.get(),
            content.get(),
            3, 
            buttons,
            nullptr
        };

        int buttonID;
        SDL_ShowMessageBox(&messageboxdata, &buttonID);
        data->button = static_cast<Button>(buttonID);

        SDL_Event event;
        event.type = static_cast<uint32_t>(Event::Type::MessageBox);
        event.user.data1 = data.get();
        SDL_PushEvent(&event);
        return static_cast<MessageBox::Button>(buttonID);
    }
    
}

}; // namespace Tsuki