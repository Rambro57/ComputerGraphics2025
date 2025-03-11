#pragma once

#include "Canis/Debug.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Window.hpp"
#include "Canis/InputManager.hpp"
#include "Canis/Data/GLTexture.hpp"

class World;

class Entity {
public:
    std::string         name;
    glm::vec3           position;
    glm::vec3           scale;
    Canis::Shader       shader;
    Canis::GLTexture    texture;
    glm::vec4           color;

    World *world = nullptr;
    Canis::Window *window = nullptr;
    Canis::InputManager *inputManager = nullptr;

    virtual void Start() {}
    virtual void Update(float _dt) {}
    virtual void Draw() {}
    virtual void OnDestroy() {}
private:
};