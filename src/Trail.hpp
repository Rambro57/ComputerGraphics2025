#pragma once

#include "Entity.hpp"

#include "World.hpp"

class Trail : public Entity {
public:
    void Start();
    void Update(float _dt);
    void Draw();
    void OnDestroy();
    
    glm::vec2 dir = glm::vec2(0.0f, 0.0f);
};