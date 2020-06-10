#ifndef TSUKI_MESSAGEBOX_H
#define TSUKI_MESSAGEBOX_H

#include <SDL2/SDL.h>
#include <string>
#include "basic.h"
#include "Event.h"

namespace Tsuki 
{

class Window;

class MessageBox
{
public:
    enum class Type
    {
        Info = SDL_MESSAGEBOX_INFORMATION,
        Warning = SDL_MESSAGEBOX_WARNING,
        Error = SDL_MESSAGEBOX_ERROR,
        Question,
    };

    using Button = Event::MessageBox::Button;

    MessageBox(const std::string& name);
    void show(const std::string& title, const std::string& content, Type type=Type::Info);
    Button show(const Window& window, const std::string& title, const std::string& content, Type type=Type::Info);


private:
    std::string m_Name;
    static Button m_ShowMessageBox(const char* name, SDL_Window* window, const char* title, const char* content, Type type);
};

}; // namespace Tsuki

#endif