#ifndef TSUKI_KEYBOARD_H
#define TSUKI_KEYBOARD_H

#include <SDL2/SDL.h>
#include "basic.h"

namespace Tsuki
{

class Keyboard
{
public:
    using KeyCode = SDL_Keycode;
    using ScanCode = SDL_Scancode;

    Keyboard() = default;
    ~Keyboard() = default;
    KeyCode keyCode(const char* key);
    KeyCode keyCode(ScanCode code);
    ScanCode scanCode(KeyCode code);
    ScanCode scanCode(const char* key);

    bool isPressed(const char* key);
    bool isPressed(KeyCode code);
    bool isPressed(ScanCode code);

private:
};

} // namespace Tsuki

#endif // TSUKI_KEYBOARD_H