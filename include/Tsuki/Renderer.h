#ifndef TSUKI_RENDERER_H
#define TSUKI_RENDERER_H

#include <SDL2/SDL.h>
#include "Window.h"
#include "Basic.h"
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

    explicit Renderer(const Window& window, RenderBy by=RenderBy::CPU);
    explicit Renderer(const Window* window, RenderBy by=RenderBy::CPU);
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = default;
    ~Renderer();

    Texture readImage(const std::string& image);
    bool writeImage(const std::string& image);

    SDL_Renderer* getRaw() const;

    int getColor(Color& color) const;
    int getColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a) const;
    int getColor(uint32_t& rgb) const;
    int setColor(const Color& color);
    int setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a=0xff);
    int setColor(uint32_t rgb, Uint8 a=0xff);

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