#ifndef TSUKI_MESSAGEBOX_H
#define TSUKI_MESSAGEBOX_H

#include <SDL2/SDL.h>
#include <string>
#include <Tsuki/Core/Basic.h>

namespace Tsuki 
{

class Window;

enum class MessageBoxType
{
    Info = SDL_MESSAGEBOX_INFORMATION,
    Warning = SDL_MESSAGEBOX_WARNING,
    Error = SDL_MESSAGEBOX_ERROR,
    Question,
};

enum class MessageBoxButton
{
    None = 0,
    Yes,
    No,
    Cancel,
};

struct MessageBoxEventData
{
    using Type = MessageBoxType;
    using Button = MessageBoxButton;

    std::string name;
    Button button;
    std::string title;
    std::string content;
};

class MessageBox
{
public:
    using Type = MessageBoxType;
    using Button = MessageBoxButton;

    MessageBox(const std::string& name) noexcept;
    void show(const std::string& title, const std::string& content, Type type=Type::Info);
    Button show(const Window* window, const std::string& title, const std::string& content, Type type=Type::Info);


private:
    std::string m_Name;
    MessageBoxEventData m_EventData;
    static Button m_ShowMessageBox(SDL_Window* window, std::shared_ptr<MessageBoxEventData> data, Type type);
};

}; // namespace Tsuki

#endif