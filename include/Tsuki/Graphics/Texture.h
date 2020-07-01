#ifndef TSUKI_TEXTURE_H
#define TSUKI_TEXTURE_H

#include <Tsuki/Core/Basic.h>
#include <string>

namespace Tsuki
{

class Renderer;

class Texture
{
public:
    enum Format
    {
        RGB24 = SDL_PIXELFORMAT_RGB24,
        RGBA32 = SDL_PIXELFORMAT_RGBA32,
    };

    explicit Texture(const Renderer& renderer, int width, int height, uint32_t format=Format::RGB24);
    explicit Texture(const Renderer* renderer, int width, int height, uint32_t format=Format::RGB24);
    explicit Texture(const Renderer& renderer, const std::string& image);
    explicit Texture(const Renderer* renderer, const std::string& image);
    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;
    ~Texture();

    SDL_Texture* getRaw() const;
    int getSize(int& width, int& height) const;
    int getFormat(uint32_t& format) const;

private:
    SDL_Texture* m_Texture;
};

} // namespace Tsuki 

#endif // TSUKI_TEXTURE_H