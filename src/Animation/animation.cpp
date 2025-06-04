#include <Animation/animation.hpp>
#include <iostream>

Animation::Animation(Texture2D texture, Vector2 scale, int frameWidth, int frameHeight, int framesCount, float frameDelay, bool looping)
    : texture(texture),
      frameDelay(frameDelay),
      looping(looping) {
    frames.reserve(framesCount);
    for (int i = 0; i < framesCount; ++i) {
        frames.push_back(Rectangle{
            static_cast<float>(i * frameWidth),
            0.0f,
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        });
    }

    this->scale.x = scale.x;
    this->scale.y = scale.y;

}

void Animation::update(float deltaTime) {
    if (is_finished && !looping) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameDelay) {
        frameTimer = 0.0f;
        currentFrame++;

        if (currentFrame >= static_cast<int>(frames.size())) {
            if (looping) {
                currentFrame = 0;
            } else {
                currentFrame = static_cast<int>(frames.size()) - 1;
                is_finished = true;
            }
        }
    }
}



void Animation::draw(Vector2 position, Color tint) const {
    const Rectangle& srcRect = frames[currentFrame];
    Rectangle destRect {
        position.x,
        position.y,
        srcRect.width * scale.x,
        srcRect.height * scale.y
    };

    
    Vector2 origin {
        (texture.width * scale.x) / (frames.size() * 2),
        (texture.height * scale.y) / frames.size()
    };

    DrawTexturePro(texture, srcRect, destRect, origin, 0.0f, tint);
}

void Animation::reset() {
    currentFrame = 0;
    frameTimer = 0.0f;
    is_finished = false;
}

bool Animation::isFinished() const {
    return is_finished;  
}

int Animation::getCurrentFrame() const {
    return currentFrame;
}