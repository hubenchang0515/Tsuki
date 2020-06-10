#include <Tsuki/Keyboard.h>
#include <Tsuki/log.hpp>

namespace Tsuki
{

Keyboard::KeyCode Keyboard::keyCode(const char* key)
{
    return SDL_GetKeyFromName(key);
}

Keyboard::KeyCode Keyboard::keyCode(ScanCode code)
{
    return SDL_GetKeyFromScancode(code);
}

Keyboard::ScanCode Keyboard::scanCode(const char* key)
{
    return SDL_GetScancodeFromName(key);
}

Keyboard::ScanCode Keyboard::scanCode(KeyCode code)
{
    return SDL_GetScancodeFromKey(code);
}

bool Keyboard::isPressed(const char* key)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    Keyboard::ScanCode index = scanCode(key);
    return state[index] == 1;
}

bool Keyboard::isPressed(KeyCode code)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    Keyboard::ScanCode index = scanCode(code);
    return state[index] == 1;
}
bool Keyboard::isPressed(ScanCode code)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[code] == 1;
}


} // namespace Tsuki