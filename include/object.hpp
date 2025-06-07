#pragma once

#include <raylib.h>
#include <box2d.h>

class Object {
public:

    void update();

    void scale(float height, float width);
    void scale(const Vector2 & scale);

    void move(const Vector2& dest);
    void move(float x, float y);
    void rotate(float degrees);

    void setPosition(const Vector2& position);
    void setPosition(float x, float y);
    void setScale(const Vector2 & scale);
    void setScale(float width, float height);
    void setVelocity(const Vector2 & velocity);
    void setAcceleration(const Vector2 & acceleration);
    void setRotate(float degrees);

    const Vector2 & getPosition() const;
    const Vector2 & getScale() const;
    const Vector2 & getVelocity() const;
    const Vector2 & getAcceleration() const;

    void createPhysicsBody(b2World* world, b2BodyType body_type, bool fixed_rotation = true);
    void destroyPhysicsBody();

    b2Body* getPhysicsBody() const;
    
    void applyForce(const Vector2 & force);
    void applyImpulse(const Vector2 & impulse);
    void setLinearVelocity(const Vector2 & velocity);

protected:

    Vector2 _position = {0.0f, 0.0f};
    Vector2 _scale = {1.0f, 1.0f};

    float _rotation = 0.0f;

    Vector2 _velocity = {0.5f, 0.5f};
    Vector2 _acceleration = {0.0f, 0.0f};

    b2Body* _physics_body = nullptr;

    int _id;
};