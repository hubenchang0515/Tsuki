#include <Tsuki/Window/Keyboard.h>

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
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    Keyboard::ScanCode index = scanCode(key);
    return state[index] == 1;
}

bool Keyboard::isPressed(KeyCode code)
{
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    Keyboard::ScanCode index = scanCode(code);
    return state[index] == 1;
}
bool Keyboard::isPressed(ScanCode code)
{
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    return state[code] == 1;
}


} // namespace Tsuki