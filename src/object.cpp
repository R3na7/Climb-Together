#include "object.hpp"
#include <iostream>

void Object::update() {

    if (_physics_body) {
        b2Vec2 new_position = _physics_body->GetPosition();
        _position = {new_position.x, new_position.y};
        std::cout << _position.x << " " << _position.y << std::endl;
        _rotation = _physics_body->GetAngle() * RAD2DEG;
    }
}

void Object::move(const Vector2& dest) {
    move(dest.x, dest.y); 
}

void Object::move(float x, float y) {
    _position.x += x;
    _position.y += y;
}

void Object::rotate(float degrees) {
    _rotation += degrees;
}

void Object::scale(float height, float width) {
    _scale.y *= height;
    _scale.x *= width;
}

void Object::scale(const Vector2 & scale) {
    _scale.y *= scale.y;
    _scale.x *= scale.x;
}

void Object::setPosition(const Vector2& position) {
    _position = position; 
}

void Object::setPosition(float x, float y) {
    _position = {x, y};
}

void Object::setScale(const Vector2 & scale) {
    _scale = scale;
}

void Object::setScale(float width, float height) {
    _scale = {width, height};
}

void Object::setVelocity(const Vector2 & velocity) {
    _velocity = velocity;
}

void Object::setAcceleration(const Vector2 & acceleration) {
    _acceleration = acceleration;
}

void Object::setRotate(float degrees){
    _rotation = degrees;
}

const Vector2 & Object::getPosition()     const { return _position; }
const Vector2 & Object::getScale()        const { return _scale; }
const Vector2 & Object::getVelocity()     const { return _velocity; }
const Vector2 & Object::getAcceleration() const { return _acceleration; }

void Object::createPhysicsBody(b2World *world, b2BodyType body_type, bool fixed_rotation) {
    b2BodyDef body_def;
    body_def.type = body_type;
    body_def.position.Set(_position.x, _position.y);
    body_def.fixedRotation = fixed_rotation;
    
    _physics_body = world->CreateBody(&body_def);

    b2PolygonShape shape;
    shape.SetAsBox(_scale.x / 2.0f, _scale.y / 2.0f);

    b2FixtureDef fixture_def;
    fixture_def.shape = &shape;
    fixture_def.density = 1.0f;
    fixture_def.friction = 0.3f;

    _physics_body->CreateFixture(&fixture_def);
}

void Object::destroyPhysicsBody() {
    if (_physics_body && _physics_body->GetWorld()) {
        _physics_body->GetWorld()->DestroyBody(_physics_body);
        _physics_body = nullptr;
    }
}

b2Body* Object::getPhysicsBody() const { return _physics_body; }

void Object::applyForce(const Vector2& force) {
    if (_physics_body) {
        _physics_body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
    }
}

void Object::applyImpulse(const Vector2& impulse) {
    if (_physics_body) {
        _physics_body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), 
                               _physics_body->GetWorldCenter(), true);
    }
}

void Object::setLinearVelocity(const Vector2& velocity) {
    if (_physics_body) {
        _physics_body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
    }
}
