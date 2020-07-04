#ifndef TSUKI_WORLD_H
#define TSUKI_WORLD_H

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Physics/Vector.h>

namespace Tsuki
{

class World
{
public:
    World();
    World(const Vec2& gravity);
    ~World()=default;

    b2World* getRaw();

    void update(float mSecond);
    void setIterations(int32_t velocity, uint32_t position);
    int32_t velocityIterations();
    int32_t positionIterations();

private:
    Vec2 m_Gravity;
    b2World m_World;
    int32_t m_VelocityIterations;
    int32_t m_PositionIterations;
};

}; // namespace Tsuki

#endif // TSUKI_H 