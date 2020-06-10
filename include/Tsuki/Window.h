#ifndef TSUKI_WINDOW_H
#define TSUKI_WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "basic.h"
#include "MessageBox.h"

namespace Tsuki 
{

class Window
{
public:
    /* 窗口坐标 */
    struct Pos 
    {
        static const int Auto = SDL_WINDOWPOS_UNDEFINED;     // 自动
        static const int Center = SDL_WINDOWPOS_CENTERED;    // 屏幕正中央
    };

    explicit Window(const std::string& title, int width, int height, int x = Pos::Auto, int y = Pos::Auto);
    ~Window();

    Window(const Window& window) = delete;
    Window(Window&& window) = default;

    SDL_Window* getRaw() const;

    void setTitle(const std::string& title);
    void getTitle(std::string& title) const;

    void setSize(int width, int height);
    void getSize(int& width, int& height) const;

    void setPos(int x, int y);
    void getPos(int& x, int& y) const;

    void show();
    void hide();
    void focus();

    MessageBox::Button messageBox(const std::string& title, const std::string& content, MessageBox::Type type=MessageBox::Type::Info);

private:
    SDL_Window* m_Window;
    int m_MessageBoxState;
};

} // namespace Tsuki 

#endif // TSUKI_WINDOW_H