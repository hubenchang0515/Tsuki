#ifndef TSUKI_BODY_HPP
#define TSUKI_BODY_HPP

#include <Tsuki/Core/Basic.h>
#include <Tsuki/Physics/World.h>
#include <Tsuki/Physics/Vector.h>
#include <vector>

namespace Tsuki
{
class Body
{
public:
    enum class Type
    {
        Static = b2_staticBody,
        Dynamic = b2_dynamicBody,
        Kinematic = b2_kinematicBody,
    };

    enum class Shape
    {
        Circle = b2Shape::e_circle,
        Edge = b2Shape::e_edge,
        Polygon = b2Shape::e_polygon,
        Chain = b2Shape::e_chain,
    };

    Body(World& world, Type type=Type::Static);
    Body(const Body& body) = delete;
    ~Body();

    b2Body* getRaw();

    Type type();
    Shape shape();

    void setType(Type type);

    void getPosition(Vec2& pos);
    void setPosition(const Vec2& pos);

    float32 angle();
    void setAngle(float32 angle);

    float32 density();
    void setDensity(float32 density);
    float32 friction();
    void setFriction(float32 friction);
    float32 restitution();
    void setRestitution(float32 restitution);

    /* Polygon Shape */
    void setAsBox(float32 halfWidth, float32 halfHeight);
    void setVertex(const std::vector<Vec2>& vertex);
    void getVertex(std::vector<Vec2>& vertex);

private:
    b2Fixture* m_Fixture();
    b2PolygonShape* m_PolygonShape();
    void m_CreatePolygonBody(const b2Vec2* points, size_t len);

private:
    Type m_Type;
    float32 m_Density;
    float32 m_Friction;
    float32 m_Restitution;
    World& m_World;
    Shape m_Shape;
    b2Body* m_Body;
};

}; // namespace Tsuki

#endif // TSUKI_H 