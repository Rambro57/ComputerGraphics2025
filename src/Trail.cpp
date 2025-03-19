#include "Trail.hpp"

using namespace glm;

void Trail::Start() {
    name = "Ball";
    position = vec3(window->GetScreenWidth() * 0.5f, window->GetScreenHeight() * 0.5f, 0.0f);
    scale = vec3(100.0f, 100.0f, 0.0f);
}

void Trail::Update(float _dt) {
    //window->SetWindowName("Pong");

    
}

void Trail::Draw() {mat4 transform = mat4(1.0f);
    transform = translate(transform, position);
    transform = glm::scale(transform, scale);

    // set shader variables
    shader.SetVec4("COLOR", color);
    shader.SetMat4("TRANSFORM", transform);
}

void Trail::OnDestroy() {
}