#pragma once

#include "Entity.hpp"

#include "World.hpp"

class Paddle : public Entity {
public:
    void Start();
    void Update();
    void Draw();
    void OnDestroy();
};