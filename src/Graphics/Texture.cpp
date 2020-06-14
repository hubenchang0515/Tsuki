#include <Tsuki/Texture.h>
#include <Tsuki/Renderer.h>
#include <Tsuki/Log.hpp>
#include <Tsuki/Exception.hpp>

namespace Tsuki
{

Texture::Texture(const Renderer& renderer, int width, int height, uint32_t format)
{
    if(renderer.getRaw() == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return;
    }

    m_Texture = SDL_CreateTexture(renderer.getRaw(), format, SDL_TEXTUREACCESS_TARGET, width, height);
    if(m_Texture == nullptr)
    {
        throw ObjectCreateError("SDL_CreateTexture(%p, %d, SDL_TEXTUREACCESS_TARGET, %d, %d) : %s", 
                renderer.getRaw(), format, width, height, SDL_GetError());
    }
}

Texture::Texture(const Renderer* renderer, int width, int height, uint32_t format)
{
    if(renderer == nullptr)
    {
        throw NullError("Tsuki::Renderer is nullptr");
        return;
    }

    if(renderer->getRaw() == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return;
    }

    m_Texture = SDL_CreateTexture(renderer->getRaw(), format, SDL_TEXTUREACCESS_TARGET, width, height);
    if(m_Texture == nullptr)
    {
        throw ObjectCreateError("SDL_CreateTexture(%p, %d, SDL_TEXTUREACCESS_TARGET, %d, %d) : %s", 
                renderer->getRaw(), format, width, height, SDL_GetError());
    }
}

Texture::Texture(const Renderer& renderer, const std::string& image)
{
    if(renderer.getRaw() == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return;
    }
    SDL_Surface* surface = IMG_Load(image.c_str());
    if(surface == nullptr)
    {
        throw IOError("IMG_Load(%s) : %s", image.c_str(), SDL_GetError());
        return;
    }
    m_Texture = SDL_CreateTextureFromSurface(renderer.getRaw(), surface);
    if(m_Texture == nullptr)
    {
        throw RenderError("SDL_CreateTextureFromSurface(%p, %p) : %s", 
                renderer.getRaw(), surface, SDL_GetError());
        return;
    }
    SDL_FreeSurface(surface);
}

Texture::Texture(const Renderer* renderer, const std::string& image)
{
    if(renderer == nullptr)
    {
        throw NullError("Tsuki::Renderer is nullptr");
        return;
    }

    if(renderer->getRaw() == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return;
    }

    SDL_Surface* surface = IMG_Load(image.c_str());
    if(surface == nullptr)
    {
        throw IOError("IMG_Load(%s) : %s", image.c_str(), SDL_GetError());
        return;
    }
    m_Texture = SDL_CreateTextureFromSurface(renderer->getRaw(), surface);
    if(m_Texture == nullptr)
    {
        throw ObjectCreateError("SDL_CreateTextureFromSurface(%p, %p) : %s", 
                renderer->getRaw(), surface, SDL_GetError());
        return;
    }
    SDL_FreeSurface(surface);
}

Texture::~Texture()
{
    if(m_Texture == nullptr)
        return;

    SDL_DestroyTexture(m_Texture);
}

SDL_Texture* Texture::getRaw() const
{
    return m_Texture;
}

int Texture::getSize(int& width, int& height) const
{
    if(m_Texture == nullptr)
    {
        throw NullError("SDL_Texture is nullptr");
        return -1;
    }

    int ret = SDL_QueryTexture(m_Texture, nullptr, nullptr, &width, &height);
    if(ret != 0)
    {
        throw IOError("SDL_QueryTexture(%p, %p, %p, %p, %p) : %s",
                    m_Texture, nullptr, nullptr, &width, &height, SDL_GetError());
    }
    return ret;
}

int Texture::getFormat(uint32_t& format) const
{
    if(m_Texture == nullptr)
    {
        throw NullError("SDL_Texture is nullptr");
        return -1;
    }

    int ret = SDL_QueryTexture(m_Texture, &format, nullptr, nullptr, nullptr);
    if(ret != 0)
    {
        throw IOError("SDL_QueryTexture(%p, %p, %p, %p, %p) : %s",
                    m_Texture, &format, nullptr, nullptr, nullptr, SDL_GetError());
    }
    return ret;
}

} // namespace Tsuki 