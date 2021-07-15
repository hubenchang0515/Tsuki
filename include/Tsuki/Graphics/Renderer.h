#ifndef TSUKI_RENDERER_H
#define TSUKI_RENDERER_H

#include <SDL2/SDL.h>
#include <Tsuki/Core/Basic.h>
#include <Tsuki/Window/Window.h>
#include <Tsuki/Graphics/Color.h>
#include <Tsuki/Exception/Exception.hpp>
#include <vector>

namespace Tsuki
{

class Texture;

class Renderer
{
public:
    enum class RenderBy
    {
        CPU = SDL_RENDERER_SOFTWARE,
        GPU = SDL_RENDERER_ACCELERATED,
    };

    enum class Flip
    {
        None = SDL_FLIP_NONE,
        Horizontal = SDL_FLIP_HORIZONTAL,
        Vertical = SDL_FLIP_VERTICAL,
        Both = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL,
    };

    explicit Renderer(const Window* window, RenderBy by=RenderBy::CPU);
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = default;
    ~Renderer();

    Texture readImage(const std::string& image);
    bool writeImage(const std::string& image);

    SDL_Renderer* getRaw() const;

    int getColor(Color& color) const;
    int getColor(uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const;
    int getColor(uint32_t& rgb) const;
    int setColor(const Color& color);
    int setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a=0xff);
    int setColor(uint32_t rgb, uint8_t a=0xff);
    int setHSVColor(const HSVColor& hsv);
    int setHSVColor(uint8_t h, uint8_t s, uint8_t v, uint8_t a=0xff);

    int getBlendMode(BlendMode& mode) const;
    int setBlendMode(BlendMode mode);

    int clear();
    void present();

    int setTarget(Texture& texture);
    int setTarget(Texture* texture);
    int getTargetSize(int& width, int& height);

    int copy(const Rect& dst, Texture& texture, const Rect& src, double angle=0, Flip flip=Flip::None);
    int copy(const Rect& dst, Texture& texture, double angle=0, Flip flip=Flip::None);
    int copy(Texture& texture, const Rect& src, double angle=0, Flip flip=Flip::None);
    int copy(Texture& texture, double angle=0, Flip flip=Flip::None);

    int putPixel(int x, int y);
    int putPixel(const Point& p);

    int drawLine(const Point& p1, const Point& p2);
    int drawLine(int x1, int y1, int x2, int y2);
    
    int drawShape(const std::vector<Point>& points);
    int fillShape(const std::vector<Point>& points);

    int drawEllipse(int x , int y , int rx, int ry);
    int fillEllipse(int x , int y , int rx, int ry);
    int drawEllipse(const Point& p, int rx, int ry);
    int fillEllipse(const Point& p, int rx, int ry);

    int drawCircle(int x , int y , int r);
    int drawCircle(const Point& p, int r);
    int fillCircle(int x , int y , int r);
    int fillCircle(const Point& p, int r);

    const Color& hsv2rgb(uint32_t h, uint32_t s, uint32_t v);

private:
    SDL_Renderer* m_Renderer;

    int m_EllipsePut4Pixel(int x, int y, int vx, int vy);

    /* 多边形扫描充填算法 */
    struct M_Edge
    {
        int ymin;
        int ymax;
        double x;
        double dx;

        M_Edge(int ymin, int ymax, double x, double dx);
    };

    void m_InitEdge(std::vector<M_Edge>& edges, const std::vector<Point>& points, int height);
    void m_ScanHorizontal(int top, int bottom, std::vector<M_Edge>& edges);

};

} // namespace Tsuki 

#endif // TSUKI_BASIC_H