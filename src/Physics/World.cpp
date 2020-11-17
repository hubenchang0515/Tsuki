#include <Tsuki/Physics/World.h>
#include <Tsuki/Exception/Exception.hpp>

namespace Tsuki
{

World::World() :
    m_Gravity({0.0f, 0.0f}),
    m_VelocityIterations(6),
    m_PositionIterations(2)
{
    m_World = new b2World(m_Gravity);
}

World::World(const Vec2& gravity) :
    m_Gravity(gravity),
    m_VelocityIterations(6),
    m_PositionIterations(2)
{
    m_World = new b2World(gravity);
}

b2World* World::getRaw()
{
    return m_World;
}

void World::update(float millisecond)
{
    if(m_World == nullptr)
    {
        throw NullError("b2World is nullptr");
        return;
    }
    m_World->Step(millisecond, m_VelocityIterations, m_PositionIterations);
}

void World::setIterations(int32_t velocity, uint32_t position)
{
    m_VelocityIterations = velocity;
    m_PositionIterations = position;
}

int32_t World::velocityIterations()
{
    return m_VelocityIterations;
}

int32_t World::positionIterations()
{
    return m_PositionIterations;
}

}; // namespace Tsuki