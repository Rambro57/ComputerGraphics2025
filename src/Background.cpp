#include "Background.hpp"

using namespace glm;

Background::Background() = default;
Background::~Background() = default;

void Background::Start() {
    name = "Background";
    position = vec3(window->GetScreenWidth() * 0.5f, window->GetScreenHeight() * 0.5f, 0.0f);
    scale = vec3(window->GetScreenWidth(), window->GetScreenHeight(), 0.0f);
    offsetX = 0.0f;
    offsetY = 0.0f;
    destroyAt0 = -1;
}

void Background::Update(float _dt) {
    offsetX += scrollSpeedX * _dt;
    offsetY += scrollSpeedY * _dt;

    if (offsetX > 1.0f) offsetX -= 1.0f;
    if (offsetY > 1.0f) offsetY -= 1.0f;
}

void Background::Draw() {
    mat4 transform = mat4(1.0f);
    transform = translate(transform, position);
    transform = glm::scale(transform, scale);

    shader.SetVec4("COLOR", color);
    shader.SetMat4("TRANSFORM", transform);
    shader.SetFloat("offsetX", offsetX);
    shader.SetFloat("offsetY", offsetY);
}

void Background::OnDestroy() {
    // Empty implementation
}
