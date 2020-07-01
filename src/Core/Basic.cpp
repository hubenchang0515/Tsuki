#include <Tsuki/Core/Basic.h>

namespace Tsuki
{

int argc = 0;
char** argv = nullptr;

bool TsukiInit(int argc, char** argv)
{
    Tsuki::argc = argc;
    Tsuki::argv = argv;
    
    return  SDL_Init(SDL_INIT_EVERYTHING) == 0 &&
            IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF) != 0;
}

void TsukiQuit()
{
    SDL_Quit();
    IMG_Quit();
}

} // namespace Tsuki 