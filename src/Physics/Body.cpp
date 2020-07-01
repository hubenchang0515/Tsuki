#include <Tsuki/Physics/Body.h>
#include <Tsuki/Exception/Exception.hpp>

namespace Tsuki
{

Body::Body(World& world, Type type):
    m_Type(type),
    m_Density(1.0f),
    m_Friction(1.0f),
    m_Restitution(0.0f),
    m_World(world),
    m_Body(nullptr)
{
    m_CreatePolygonBody(nullptr, 0);
}

Body::~Body()
{
    if(m_Body != nullptr)
        m_World.getRaw()->DestroyBody(m_Body);
}

b2Body* Body::getRaw()
{
    return m_Body;
}

Body::Type Body::type()
{
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
        return Type::Static;
    }
    return m_Type;
}

Body::Shape Body::shape()
{
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
    }
    return m_Shape;
}

void Body::setType(Type type)
{
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
        return;
    }
    m_Body->SetType(static_cast<b2BodyType>(type));
    m_Type = type;
}

void Body::getPosition(Vec2& pos)
{
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
        return;
    }
    pos = m_Body->GetPosition();
}

void Body::setPosition(const Vec2& pos)
{
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
        return;
    }
    
    float32 angle = m_Body->GetAngle();
    m_Body->SetTransform(pos, angle);
}

float32 Body::angle()
{
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
        return 0.0f;
    }
    return m_Body->GetAngle();
}

void Body::setAngle(float32 angle)
{
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
        return;
    }

    m_Body->SetTransform(m_Body->GetPosition(), angle);
}

float32 Body::density()
{
    b2Fixture* fixture = m_Fixture();
    return fixture->GetDensity();
}

void Body::setDensity(float32 density)
{
    b2Fixture* fixture = m_Fixture();
    fixture->SetDensity(density);
    m_Body->ResetMassData();
}

float32 Body::friction()
{
    b2Fixture* fixture = m_Fixture();
    return fixture->GetFriction();
}

void Body::setFriction(float32 friction)
{
    b2Fixture* fixture = m_Fixture();
    fixture->SetFriction(friction);
    m_Body->ResetMassData();
}

float32 Body::restitution()
{
    b2Fixture* fixture = m_Fixture();
    return fixture->GetRestitution();
}

void Body::setRestitution(float32 restitution)
{
    b2Fixture* fixture = m_Fixture();
    fixture->SetRestitution(restitution);
    m_Body->ResetMassData();
}

void Body::setAsBox(float32 halfWidth, float32 halfHeight)
{
    b2PolygonShape* shape = m_PolygonShape();
    shape->SetAsBox(halfWidth, halfHeight);
    m_Body->ResetMassData();

    // std::vector<b2Vec2> points;
    // points.emplace_back(-halfWidth, -halfHeight);
    // points.emplace_back(halfWidth, -halfHeight);
    // points.emplace_back(halfWidth, halfHeight);
    // points.emplace_back(-halfWidth, halfHeight);
    // m_CreatePolygonBody(points.data(), points.size());
}

void Body::setVertex(const std::vector<Vec2>& vertex)
{
    b2PolygonShape* shape = m_PolygonShape();
    shape->Set(vertex.data(), vertex.size());
    m_Body->ResetMassData();

    // size_t len = vertex.size();
    // m_CreatePolygonBody(vertex.data(), len);
}

void Body::getVertex(std::vector<Vec2>& vertex)
{
    b2PolygonShape* shape = m_PolygonShape();
    size_t len = shape->GetVertexCount();
    vertex.resize(0);
    vertex.reserve(len);
    for(size_t i = 0; i < len; i++)
    {
        b2Vec2 p = shape->GetVertex(i);
        p = m_Body->GetWorldPoint(p);
        vertex.push_back(p);
    }
}


b2Fixture* Body::m_Fixture()
{
    if(m_Body == nullptr || m_Body->GetFixtureList() == nullptr)
    {
        throw NullError("b2Body or b2Fixture is nullptr");
        return nullptr;
    }
    return m_Body->GetFixtureList();
}

b2PolygonShape* Body::m_PolygonShape()
{
    if(m_Body == nullptr || m_Body->GetFixtureList() == nullptr || m_Body->GetFixtureList()[0].GetShape() == nullptr)
    {
        throw NullError("b2Body or b2Fixture or b2Shape is nullptr");
        return nullptr;
    }

    if(m_Shape != Shape::Polygon || m_Body->GetFixtureList()[0].GetShape()->GetType() != b2Shape::e_polygon)
    {
        throw RuntimeError("Shape type %d is not Shape::Type::Polygon", static_cast<int>(m_Shape));
        return nullptr;
    }

    return dynamic_cast<b2PolygonShape*>(m_Body->GetFixtureList()[0].GetShape());
}

void Body::m_CreatePolygonBody(const b2Vec2* points, size_t len)
{
    if(points != nullptr && len < 3)
    {
        throw RuntimeError("PolygonBody vectex %p count %lu < 3", points, len);
    }
    float32 angle {0};
    b2Vec2 pos {0,0};
    if(m_Body != nullptr)
    {
        angle = m_Body->GetAngle();
        pos = m_Body->GetPosition();
        m_World.getRaw()->DestroyBody(m_Body);
    }

    b2PolygonShape shape;
    if(points != nullptr && len >= 3)
    {
        shape.Set(points, len);
    }
    else
    {
        shape.SetAsBox(1.0f, 1.0f);
    }
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = m_Density;
    fixtureDef.friction = m_Friction;
    fixtureDef.restitution = m_Restitution;

    b2BodyDef bodyDef;
    bodyDef.angle = angle;
    bodyDef.position = pos;
    bodyDef.type = static_cast<b2BodyType>(m_Type);
    m_Body = m_World.getRaw()->CreateBody(&bodyDef);
    m_Body->CreateFixture(&fixtureDef);
    if(m_Body == nullptr)
    {
        throw NullError("b2Body is nullptr");
        return;
    }
    m_Shape = Shape::Polygon;
}

}; // namespace Tsuki
