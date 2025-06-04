#pragma once
#include "raylib.h"
#include <vector>
#include <memory>

class Animation {
public:
    Animation(Texture2D texture, Vector2 scale, int frameWidth, int frameHeight, int framesCount, float frameDelay, bool looping=true);
    ~Animation() = default;

    void update(float deltaTime);
    void draw(Vector2 position, Color tint = WHITE) const;
    void reset();

    bool isFinished() const;
    int getCurrentFrame() const;
    
private:
    Texture2D texture;  // Текстура с кадрами
    std::vector<Rectangle> frames;
    Vector2 scale;
    Vector2 origin;

    int currentFrame = 0;
    float frameDelay;
    float frameTimer = 0.0f;
    bool looping;
    bool is_finished = false;
};