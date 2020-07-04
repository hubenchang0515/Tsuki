#include <Tsuki/Graphics/Color.h>
#include <Tsuki/Exception/Exception.hpp>
#include <algorithm>
#include <cmath>

namespace Tsuki
{

const Color& Convert2RGB(const HSVColor& hsv)
{
    if(hsv.h > 180)
    {
        throw RuntimeError("HSVColor::Hue > 180");
    }
    float H = hsv.h;
    float S = hsv.s / 255.0; 
    float V = hsv.v / 255.0;


    float C = V * S;
    float X = C * (1 - fabs( fmod(H / 30 , 2) - 1));
    float m = V - C;

    float r=0,g=0,b=0;
    switch(int(H / 30))
    {
    case 0 :
    case 6 :
        r = C;
        g = X;
        break;

    case 1 :
        r = X;
        g = C;
        break;

    case 2 :
        g = C;
        b = X;
        break;

    case 3 :
        g = X;
        b = C;
        break;

    case 4 :
        r = X;
        b = C;
        break;

    case 5 :
        r = C;
        b = X;
        break;
    }

    static RGBColor p;
    p.r = (r + m) * 255;
    p.g = (g + m) * 255;
    p.b = (b + m) * 255;
    p.a = hsv.a;

    return p;
}

const HSVColor& Convert2HSV(const RGBColor& rgb)
{
    static HSVColor p;
    p.a = rgb.a;
    p.v = std::max({rgb.r, rgb.g, rgb.b});
    int16_t min = std::min({rgb.r, rgb.g, rgb.b});
    int16_t delta = p.v - min;
    if(p.v == 0)
    {
        p.s = 0;
        p.h = 0;
    }
    else
    {
        p.s = 255 - 255 * std::min({rgb.r, rgb.g, rgb.b}) / p.v;

        if(p.v == min)
            p.h = 0;
        else if(p.v == rgb.r && rgb.g >= rgb.b)
            p.h = 30 * (rgb.g - rgb.b) / delta;
        else if(p.v == rgb.r && rgb.g < rgb.b)
            p.h = 30 * (rgb.g - rgb.b) / delta + 180;
        else if(p.v == rgb.g)
            p.h = 30 * (rgb.b - rgb.r) / delta + 60;
        else
            p.h = 30 * (rgb.r - rgb.g) / delta + 120;
    }


    return p;
}

}; // namespace Tsuki