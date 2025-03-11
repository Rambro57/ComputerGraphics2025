#pragma once

#include "Entity.hpp"

#include "World.hpp"

class Ball : public Entity {
public:
    void Start() {
        using namespace glm;
        name = "Ball";
        position = vec3(window->GetScreenWidth() * 0.5f, window->GetScreenHeight() * 0.5f, 0.0f);
        scale = vec3(100.0f, 100.0f, 0.0f);
    }

    void Update(float _dt) {
        using namespace glm;

        window->SetWindowName("Pong");
        
        if (position.y > window->GetScreenHeight() - (scale.y * 0.5f)) {
            position.y = window->GetScreenHeight() - (scale.y * 0.5f);
            dir.y = abs(dir.y) * -1.0f;
        }
        if (position.y < scale.y * 0.5f) {
            position.y = scale.y * 0.5f;
            dir.y = abs(dir.y);
        }
        if (position.x > window->GetScreenWidth() - (scale.x * 0.5f)) {
            position.x = window->GetScreenWidth() - (scale.x * 0.5f);
        }
        if (position.x < scale.x * 0.5f) {
            position.x = scale.x * 0.5f;
        }

        if (dir != vec2(0.0f))
            position += vec3(dir.x, dir.y, 0.0f) * speed * _dt;
    }

    void Draw() {
        using namespace glm;

        mat4 transform = mat4(1.0f);
        transform = translate(transform, position);
        transform = glm::scale(transform, scale);

        // set shader variables
        shader.SetVec4("COLOR", color);
        shader.SetMat4("TRANSFORM", transform);
    }

    void OnDestroy() {
        using namespace glm;
    }

    float speed = 100.0f;
    glm::vec2 dir = glm::vec2(1.0f, 1.0f);
};