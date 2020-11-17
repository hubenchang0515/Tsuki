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
    static Body createPolygonBody(const std::vector<Vec2>& vertex);
    static Body createCircleBody(const Vec2& center, float radius);

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

    Body(World& world, Shape shape, Type type=Type::Static);
    Body(const Body& body) = delete;
    ~Body();

    b2Body* getRaw();

    Type type();
    Shape shape();

    void setType(Type type);

    void getPosition(Vec2& pos);
    void setPosition(const Vec2& pos);

    float angle();
    void setAngle(float angle);

    float radius();
    void setRadius(float radius);

    float density();
    void setDensity(float density);
    float friction();
    void setFriction(float friction);
    float restitution();
    void setRestitution(float restitution);

    /* Polygon Shape */
    void setAsBox(float halfWidth, float halfHeight);
    void setVertex(const std::vector<Vec2>& vertex);
    void getVertex(std::vector<Vec2>& vertex);

private:
    b2Fixture* m_Fixture();

    b2PolygonShape* m_PolygonShape();
    void m_CreatePolygonBody(const std::vector<Vec2>& points);

    b2CircleShape* m_CircleShape();
    void m_CreateCircleBody(const b2Vec2& center, float radius);

    b2ChainShape* m_ChainShape();
    void m_CreateChainBody(const std::vector<Vec2> points);

    b2EdgeShape* m_EdgeShape();
    void m_CreateEdgeBody(const b2Vec2& p1, const b2Vec2& p2);

private:
    Type m_Type;
    float m_Density;
    float m_Friction;
    float m_Restitution;
    World& m_World;
    Shape m_Shape;
    b2Body* m_Body;
};

}; // namespace Tsuki

#endif // TSUKI_H 