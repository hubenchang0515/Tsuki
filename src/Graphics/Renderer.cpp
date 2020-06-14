#include <Tsuki/Renderer.h>
#include <Tsuki/Texture.h>
#include <Tsuki/Log.hpp>
#include <Tsuki/Exception.hpp>
#include <cmath>
#include <algorithm>
#include <vector>

namespace Tsuki
{

Renderer::Renderer(const Window& window, Renderer::RenderBy by)
{
    if(window.getRaw() == nullptr)
    {
        throw NullError("SDL_Window is nullptr");
        return;
    }
    m_Renderer = SDL_CreateRenderer(window.getRaw(), -1, static_cast<uint32_t>(by) | SDL_RENDERER_TARGETTEXTURE);
    if(m_Renderer == nullptr)
    {
        throw ObjectCreateError("SDL_CreateRenderer(%p, -1, %d) : %s", window.getRaw(), static_cast<int>(by), SDL_GetError());
    }
}

Renderer::Renderer(const Window* window, Renderer::RenderBy by)
{
    if(window == nullptr)
    {
        throw NullError("Tsuki::Window is nullptr");
        return;
    }
    
    if(window->getRaw() == nullptr)
    {
        throw NullError("SDL_Window is nullptr");
        return;
    }

    m_Renderer = SDL_CreateRenderer(window->getRaw(), -1, static_cast<uint32_t>(by) | SDL_RENDERER_TARGETTEXTURE);
    if(m_Renderer == nullptr)
    {
        throw ObjectCreateError("SDL_CreateRenderer(%p, -1, %d) : %s", window->getRaw(), static_cast<int>(by), SDL_GetError());
    }
}

Renderer::~Renderer()
{
    if(m_Renderer == nullptr)
        return;

    SDL_DestroyRenderer(m_Renderer);
}

Texture Renderer::readImage(const std::string& image)
{
    return Texture(this, image);
}

bool Renderer::writeImage(const std::string& image)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return false;
    }

    int width, height;
    getTargetSize(width, height);
    void* pixels = malloc(static_cast<size_t>(4 * width * height));

    if(pixels == nullptr)
    {
        throw MemoryError("malloc(%lu) : %s", static_cast<size_t>(4 * width * height), strerror(errno));
        return false;
    }

    if(0 != SDL_RenderReadPixels(m_Renderer, nullptr, SDL_PIXELFORMAT_ARGB8888, pixels, 4*width))
    {
        throw RenderError("SDL_RenderReadPixels(%p, nullptr, SDL_PIXELFORMAT_ARGB8888, %p, 0) : %s",
                                m_Renderer, pixels, SDL_GetError());
        return false;
    }

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, 32, 4*width,
                                                                SDL_PIXELFORMAT_ARGB8888);
    if(surface == nullptr)
    {
        throw RenderError("SDL_CreateRGBSurfaceWithFormatFrom(%p, %d, %d, 32, %d, SDL_PIXELFORMAT_ARGB8888) : %s",
                pixels, width, height, 4*width, SDL_GetError());
        return false;
    }
    
    if(0 != SDL_SaveBMP(surface, image.c_str()))
    {
        throw IOError("SDL_SaveBMP(%p, %s) : %s", surface, image.c_str(), SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);
    free(pixels);
    return true;
}

SDL_Renderer* Renderer::getRaw() const
{
    return m_Renderer;
}

int Renderer::getColor(Color& color) const
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_GetRenderDrawColor(m_Renderer, &color.r, &color.g, &color.b, &color.a);
    if(ret != 0)
    {
        throw RenderError("SDL_GetRenderDrawColor(%p, %p, %p, %p, %p) : %s",
                        m_Renderer, &color.r, &color.g, &color.b, &color.a, SDL_GetError());
    }
    return ret;
}

int Renderer::getColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a) const
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_GetRenderDrawColor(m_Renderer, &r, &g, &b, &a);
    if(ret != 0)
    {
        throw RenderError("SDL_GetRenderDrawColor(%p, %p, %p, %p, %p) : %s",
                        m_Renderer, &r, &g, &b, &a, SDL_GetError);
    }
    return ret;
}

int Renderer::getColor(uint32_t& rgb) const
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    Uint8 r, g, b, a;
    int ret = SDL_GetRenderDrawColor(m_Renderer, &r, &g, &b, &a);
    if(ret != 0)
    {
        throw RenderError("SDL_GetRenderDrawColor(%p, %p, %p, %p, %p) : %s",
                        m_Renderer, &r, &g, &b, &a, SDL_GetError());
    }
    rgb = (r << 16) | (g << 8) | a;
    return ret;
}

int Renderer::setColor(const Color& color)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
    if(ret != 0)
    {
        throw RenderError("SDL_SetRenderDrawColor(%p, 0x%x, 0x%x, 0x%x, 0x%x) : %s",
                        m_Renderer, color.r, color.g, color.b, color.a, SDL_GetError());
    }
    return ret;
}

int Renderer::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    if(ret != 0)
    {
        throw RenderError("SDL_SetRenderDrawColor(%p, 0x%x, 0x%x, 0x%x, 0x%x) : %s",
                        m_Renderer, r, g, b, a, SDL_GetError());
    }
    return ret;
}

int Renderer::setColor(uint32_t rgb, Uint8 a)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    Uint8 r, g, b;
    r = static_cast<Uint8>((rgb >> 16) & 0xff);
    g = static_cast<Uint8>((rgb >> 8) & 0xff);
    b = static_cast<Uint8>(rgb & 0xff);

    int ret = SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    if(ret != 0)
    {
        throw RenderError("SDL_SetRenderDrawColor(%p, 0x%x, 0x%x, 0x%x, 0x%x) : %s",
                        m_Renderer, r, g, b, a, SDL_GetError());
    }
    return ret;
}

int Renderer::getBlendMode(BlendMode& mode) const
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    SDL_BlendMode _mode;
    int ret = SDL_GetRenderDrawBlendMode(m_Renderer, &_mode);
    if(ret != 0)
    {
        throw RenderError("SDL_GetRenderDrawBlendMode(%p, %p) : %s", 
                        m_Renderer, &_mode, SDL_GetError());
    }
    mode = static_cast<BlendMode>(_mode);
    return ret;
}

int Renderer::setBlendMode(BlendMode mode)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_SetRenderDrawBlendMode(m_Renderer, static_cast<SDL_BlendMode>(mode));
    if(ret != 0)
    {
        throw RenderError("SDL_SetRenderDrawBlendMode(%p, %d) : %s", 
                        m_Renderer, static_cast<SDL_BlendMode>(mode), SDL_GetError());
    }
    return ret;
}

int Renderer::clear()
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_RenderClear(m_Renderer);
    if(ret != 0)
    {
        throw RenderError("SDL_RenderClear(%p) : %s", m_Renderer, SDL_GetError());
    }
    return ret;
}

void Renderer::present()
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return;
    }

    SDL_RenderPresent(m_Renderer);
}

int Renderer::setTarget(Texture& texture)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    if(texture.getRaw() == nullptr)
    {
        throw NullError("SDL_Texture is nullptr");
        return -1;
    }

    int ret = SDL_SetRenderTarget(m_Renderer, texture.getRaw());
    if(ret != 0)
    {
        throw RenderError("SDL_SetRenderTarget(%p, %p) : %s", 
                        m_Renderer, texture.getRaw(), SDL_GetError());
    }
    return ret;
}

int Renderer::setTarget(Texture* texture)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_SetRenderTarget(m_Renderer, texture ? texture->getRaw() : nullptr);
    if(ret != 0)
    {
        throw RenderError("SDL_SetRenderTarget(%p, %p) : %s", m_Renderer, 
                            texture ? texture->getRaw() : nullptr, SDL_GetError());
    }
    return ret;
}

int Renderer::getTargetSize(int& width, int& height)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_GetRendererOutputSize(m_Renderer, &width, &height);
    if(ret != 0)
    {
        throw RenderError("SDL_GetRendererOutputSize(%p, %p, %p) : %s",
                        m_Renderer, &width, &height, SDL_GetError());
    }
    return ret;
}

int Renderer::copy(const Rect& dst, Texture& texture, const Rect& src, double angle, Flip flip)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    if(texture.getRaw() == nullptr)
    {
        throw NullError("SDL_Texture is nullptr");
        return -1;
    }

    int ret = SDL_RenderCopyEx(m_Renderer, texture.getRaw(), &src, &dst, 
                            angle, nullptr, static_cast<SDL_RendererFlip>(flip));
    if(ret != 0)
    {
        throw RenderError("SDL_RenderCopyEx(%p, %p, %p, %p, %lf, %p, 0x%x ) : %s",
                        m_Renderer, texture.getRaw(), &src, &dst, angle, nullptr, 
                        static_cast<uint32_t>(flip), SDL_GetError());
    }
    return ret;
}

int Renderer::copy(const Rect& dst, Texture& texture, double angle, Flip flip)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    if(texture.getRaw() == nullptr)
    {
        throw NullError("SDL_Texture is nullptr");
        return -1;
    }

    int ret = SDL_RenderCopyEx(m_Renderer, texture.getRaw(), nullptr, &dst, angle, 
                            nullptr, static_cast<SDL_RendererFlip>(flip));
    if(ret != 0)
    {
        throw RenderError("SDL_RenderCopyEx(%p, %p, %p, %p, %lf, %p, 0x%x ) : %s",
                        m_Renderer, texture.getRaw(), nullptr, &dst, angle, nullptr, 
                        static_cast<uint32_t>(flip), SDL_GetError());
    }
    return ret;
}

int Renderer::copy(Texture& texture, const Rect& src, double angle, Flip flip)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    if(texture.getRaw() == nullptr)
    {
        throw NullError("SDL_Texture is nullptr");
        return -1;
    }

    int ret = SDL_RenderCopyEx(m_Renderer, texture.getRaw(), &src, nullptr, angle, 
                            nullptr, static_cast<SDL_RendererFlip>(flip));
    if(ret != 0)
    {
        throw RenderError("SDL_RenderCopyEx(%p, %p, %p, %p, %lf, %p, 0x%x ) : %s",
                        m_Renderer, texture.getRaw(), &src, nullptr, angle, nullptr, 
                        static_cast<uint32_t>(flip), SDL_GetError());
    }
    return ret;
}

int Renderer::copy(Texture& texture, double angle, Flip flip)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    if(texture.getRaw() == nullptr)
    {
        throw NullError("SDL_Texture is nullptr");
        return -1;
    }

    int ret = SDL_RenderCopyEx(m_Renderer, texture.getRaw(), nullptr, nullptr, angle, 
                            nullptr, static_cast<SDL_RendererFlip>(flip));
    if(ret != 0)
    {
        throw RenderError("SDL_RenderCopyEx(%p, %p, %p, %p, %lf, %p, 0x%x ) : %s",
                        m_Renderer, texture.getRaw(), nullptr, nullptr, angle, nullptr, 
                        static_cast<uint32_t>(flip), SDL_GetError());
    }
    return ret;
}

int Renderer::drawLine(const Point& p1, const Point& p2)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_RenderDrawLine(m_Renderer, p1.x, p1.y, p2.x, p2.y);
    if(ret != 0)
    {
        throw RenderError("SDL_RenderDrawLine(%p, %d, %d, %d, %d) : %s",
                        m_Renderer, p1.x, p1.y, p2.x, p2.y, SDL_GetError());
    }
    return ret;
}

int Renderer::drawLine(int x1, int y1, int x2, int y2)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    int ret = SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
    if(ret != 0)
    {
        throw RenderError("SDL_RenderDrawLine(%p, %d, %d, %d, %d) : %s",
                        m_Renderer, x1, y1, x2, y2, SDL_GetError());
    }
    return ret;
}

int Renderer::drawShape(const std::vector<Point>& points)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    size_t n = points.size();
    if(n < 3)
    {
        throw RenderError("Renderer::fillShape points count %lu < 3", n);
        return -1;
    }

    this->drawLine(points[0], points[n-1]);
    int ret = SDL_RenderDrawLines(m_Renderer, points.data(), points.size());
    if(ret != 0)
    {
        throw RenderError("SDL_RenderDrawLines(%p, %p, %lu) : %s", 
                        m_Renderer, points.data(), points.size(), SDL_GetError());
    }
    return ret;
}

int Renderer::fillShape(const std::vector<Point>& points)
{
    if(m_Renderer == nullptr)
    {
        throw NullError("SDL_Renderer is nullptr");
        return -1;
    }

    size_t n = points.size();
    if(n < 3)
    {
        throw RenderError("Renderer::fillShape points count %lu < 3", n);
        return -1;
    }

    auto higher = [](const Point& p1, const Point& p2) -> bool { return p1.y < p2.y; };
    const Point& top = *std::min_element(points.begin(), points.end(), higher);
    const Point& bottom = *std::max_element(points.begin(), points.end(), higher);

    int width, height;
    std::vector<Renderer::Edge> edges;
    this->getTargetSize(width, height);
    this->initEdge(edges, points, height);
    this->scanHorizontal(std::max(top.y, 0), std::min(bottom.y, height), edges);

    return 0;
}

void Renderer::initEdge(std::vector<Renderer::Edge>& edges, const std::vector<Point>& points, int height)
{
    size_t n = points.size();
    edges.reserve(n);
    for(size_t i = 0; i < n; i++)
    {
        size_t next = (i + 1) % n;
        if(points[i].y == points[next].y)
        {
            continue;
        }
        else if(points[i].y <= points[next].y)
        {
            double dx = static_cast<double>(points[next].x - points[i].x) / (points[next].y - points[i].y);
            int ymin = points[i].y >= 0 ? points[i].y : 0;
            int ymax = points[next].y <= height ? points[next].y : height;
            double x = points[i].y >= 0 ? points[i].x : points[i].x - dx * points[i].y;
            edges.emplace_back(ymin, ymax, x, dx);
        }
        else
        {
            double dx = static_cast<double>(points[i].x - points[next].x) / (points[i].y - points[next].y);
            int ymin = points[next].y >= 0 ? points[next].y : 0;
            int ymax = points[i].y <= height ? points[i].y : height;
            double x = points[next].y >= 0 ? points[next].x : points[next].x - dx * points[next].y;
            edges.emplace_back(ymin, ymax, x, dx);
        }
    }
}


void Renderer::scanHorizontal(int top, int bottom, std::vector<Edge>& edges)
{
    for(int y = top; y < bottom; y++)
    {
        std::vector<int> p;
        for(auto& edge : edges)
        {
            if(y < edge.ymin || y >= edge.ymax)
                continue;

            p.emplace_back(edge.x);
            edge.x += edge.dx;
        }

        std::sort(p.begin(), p.end());
        for(size_t i = 0; i + 1 < p.size(); i += 2)
        {
            this->drawLine(p[i], y, p[i+1], y);
        }
    }
}

Renderer::Edge::Edge(int ymin, int ymax, double x, double dx) :
    ymin(ymin), ymax(ymax), x(x), dx(dx)
{

}

} // namespace Tsuki 

