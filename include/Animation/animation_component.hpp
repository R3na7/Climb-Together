#pragma once
#include "raylib.h"
#include "animation.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>

class AnimationComponent {
public:
    AnimationComponent() = default;
    ~AnimationComponent() = default;

    void addAnimation(const std::string& name);
    void play(const std::string& name, bool forceReset = false);
    void update(float deltaTime);
    void draw(Vector2 position, Color tint = WHITE) const;

    void setAnimation(const std::string& name,Texture2D texture, Vector2 scale, int frameWidth, int frameHeight, int framesCount, float frameDelay, bool looping=true);

    bool isCurrentAnimationFinished() const;

    const std::string& getCurrentAnimationName() const;

private:
    std::unordered_map<std::string, std::optional<Animation>> animations;
    Animation* currentAnimation = nullptr;  // Не владеем, просто наблюдаем
    std::string name;
};