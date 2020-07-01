#include <Tsuki/Event/EventQuit.h>

namespace Tsuki
{

bool Event::Quit::push()
{
    SDL_Event event;
    event.type = static_cast<uint32_t>(Event::Type::Quit);
    int ret = SDL_PushEvent(&event);
    if(ret != 1)
    {
        throw RuntimeError("SDL_PushEvent(%p) : %s", &event, SDL_GetError());
    }
    return ret == 1;
}

}; // namespace Tsuki