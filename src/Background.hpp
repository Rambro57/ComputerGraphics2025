#pragma once

#include "Entity.hpp"
#include "World.hpp"

class Background : public Entity {
    public:
        Background();              // Constructor declaration
        virtual ~Background();     // Virtual destructor declaration
    
        void Start() override;
        void Update(float _dt) override;
        void Draw() override;
        void OnDestroy() override;
    
        float scrollSpeedX = 0.1f;
        float scrollSpeedY = 0.075f;
        float offsetX = 0.0f;
        float offsetY = 0.0f;
    };
    