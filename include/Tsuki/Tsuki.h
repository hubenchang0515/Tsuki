#ifndef TSUKI_H
#define TSUKI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Core/Log.hpp>
#include <Tsuki/Core/Timer.h>

#include <Tsuki/Exception/Exception.hpp>

#include <Tsuki/Window/Window.h>
#include <Tsuki/Window/MessageBox.h>
#include <Tsuki/Window/Keyboard.h>

#include <Tsuki/Graphics/Renderer.h>
#include <Tsuki/Graphics/Texture.h>

#include <Tsuki/Event/Event.h>

#include <Tsuki/Physics/World.h>
#include <Tsuki/Physics/Body.h>

#if defined(main) && !defined(SDL_MAIN_NEEDED)
#   undef main
#endif

#endif // TSUKI_H 