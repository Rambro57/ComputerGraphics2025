#include "Paddle.hpp"

#include "World.hpp"

using namespace glm;

void Paddle::Start() {
    scale = vec3(20.0f, 100.0f, 0.0f);
}

void Paddle::Update() {
    if (name == "RightPaddle")
    {
        position = glm::vec3(window->GetScreenWidth() * 0.9f, window->GetScreenHeight() * 0.5f + sin(SDL_GetTicks() / 1000.0f)*100.0f, 0.0f);
    } else {
        position = glm::vec3(window->GetScreenWidth() * 0.1f, window->GetScreenHeight() * 0.5f + cos(SDL_GetTicks() / 1000.0f)*100.0f, 0.0f);
    }
}

void Paddle::Draw() {
    mat4 transform = mat4(1.0f);
    transform = translate(transform, position);
    transform = glm::scale(transform, scale);

    // set shader variables
    shader.SetVec4("COLOR", color);
    shader.SetMat4("TRANSFORM", transform);
}

void Paddle::OnDestroy() {
    
}