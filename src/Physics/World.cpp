#include <Tsuki/Physics/World.h>

namespace Tsuki
{

World::World() :
    m_Gravity({0.0f, 0.0f}),
    m_World(b2Vec2{0.0f, 0.0f}),
    m_VelocityIterations(6),
    m_PositionIterations(2)
{
    
}

World::World(const Vec2& gravity) :
    m_Gravity(gravity),
    m_World(gravity),
    m_VelocityIterations(6),
    m_PositionIterations(2)
{
    
}

b2World* World::getRaw()
{
    return &m_World;
}

void World::update(float millisecond)
{
    m_World.Step(millisecond, m_VelocityIterations, m_PositionIterations);
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