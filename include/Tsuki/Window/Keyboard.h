#ifndef TSUKI_KEYBOARD_H
#define TSUKI_KEYBOARD_H

#include <SDL2/SDL.h>
#include <Tsuki/Core/Basic.h>

namespace Tsuki
{

class Keyboard
{
public:
    using KeyCode = SDL_Keycode;
    using ScanCode = SDL_Scancode;

    Keyboard() = default;
    ~Keyboard() = default;
    static KeyCode keyCode(const char* key);
    static KeyCode keyCode(ScanCode code);
    static ScanCode scanCode(KeyCode code);
    static ScanCode scanCode(const char* key);

    static bool isPressed(const char* key);
    static bool isPressed(KeyCode code);
    static bool isPressed(ScanCode code);

private:
};

} // namespace Tsuki

#endif // TSUKI_KEYBOARD_H