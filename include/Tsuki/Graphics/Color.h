#ifndef TSUKI_COLOR
#define TSUKI_COLOR

#include <SDL2/SDL.h>

namespace Tsuki
{

using Color = SDL_Color;
using RGBColor = SDL_Color;

struct HSVColor
{
    uint8_t h;
    uint8_t s;
    uint8_t v;
    uint8_t a;
};

const RGBColor& Convert2RGB(const HSVColor& hsv);
const HSVColor& Convert2HSV(const RGBColor& rgb);

}; // namespace Tsuki

#endif