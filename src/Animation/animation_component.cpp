#include <Animation/animation_component.hpp>
#include <iostream>

void AnimationComponent::addAnimation(const std::string& name) {
    animations.insert({name,std::nullopt});
}

void AnimationComponent::play(const std::string& name, bool forceReset) {
    auto it = animations.find(name);
    if (it == animations.end()) return;  // Анимация не найдена
    if (currentAnimation == &it->second.value() && !forceReset) return;  // Уже играет

    currentAnimation = &it->second.value();
    this->name = name;
}

void AnimationComponent::update(float deltaTime) {
    if (currentAnimation) {
        currentAnimation->update(deltaTime);
    }
}

void AnimationComponent::setAnimation(const std::string& name,Texture2D texture, Vector2 scale, int frameWidth, int frameHeight, int framesCount, float frameDelay, bool looping) {
    animations[name] = {
        texture,
        scale,
        frameWidth,
        frameHeight,
        framesCount,
        frameDelay,
        looping
    };
}



void AnimationComponent::draw(Vector2 position, Color tint) const {
    if (currentAnimation) 
        currentAnimation->draw(position, tint);
}

bool AnimationComponent::isCurrentAnimationFinished() const {
    return currentAnimation ? currentAnimation->isFinished() : false;
}

const std::string& AnimationComponent::getCurrentAnimationName() const {
    return name;
}