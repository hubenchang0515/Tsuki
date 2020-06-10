#ifndef TSUKI_BASIC_H
#define TSUKI_BASIC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <thread>
#include <mutex>
#include <cstdint>

namespace Tsuki
{

extern int argc;
extern char** argv;

bool TsukiInit(int argc = 0, char** argv = nullptr);
void TsukiQuit();
void TsukiDelay(uint32_t ms);

using Color = SDL_Color;
using Rect = SDL_Rect;
using Point = SDL_Point;

using Thread = std::thread;
using Mutex = std::mutex;

struct Line
{
    int x1, y1;
    int x2, y2;
};

enum class BlendMode
{
    None = SDL_BLENDMODE_NONE,
    Blend = SDL_BLENDMODE_BLEND,
    Add = SDL_BLENDMODE_ADD,
    Modulate = SDL_BLENDMODE_MOD,
};

} // namespace Tsuki 

#endif // TSUKI_BASIC_H