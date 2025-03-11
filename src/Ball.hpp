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
};