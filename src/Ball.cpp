#include "Ball.hpp"

#include "Paddle.hpp"

using namespace glm;

void Ball::Start() {
    name = "Ball";
    
    if(world->close){
        position = vec3(window->GetScreenWidth() * 0.5f, window->GetScreenHeight() * 1.0f, 0.0f);
    }
    else{
        position = vec3(window->GetScreenWidth() * 0.5f, window->GetScreenHeight() * 0.5f, 0.0f);
    }
    scale = vec3(100.0f, 100.0f, 0.0f);
    destroyAt0 = -1;
}

void Ball::Update(float _dt) {
    //window->SetWindowName("Pong");

    if (dir == vec2(0.0f))
    {
        if (world->close){
            float randX = (float)rand()/RAND_MAX;
            float randY = (float)rand()/RAND_MAX;
            if(rand() > RAND_MAX/2){ randX = -randX; }
            dir = vec2(randX, randY);
        }
        else if (inputManager->GetKey(SDL_SCANCODE_SPACE))
        {
            vec2 directions[] = {vec2(1.0f, 1.0f), vec2(1.0f, -1.0f), vec2(-1.0f, 1.0f), vec2(-1.0f, -1.0f)};
            dir = directions[rand()%4];
        }
    }
    
    if (position.y > window->GetScreenHeight() - (scale.y * 0.5f)) {
        position.y = window->GetScreenHeight() - (scale.y * 0.5f);
        dir.y = abs(dir.y) * -1.0f;
    }
    if (position.y < scale.y * 0.5f) {
        position.y = scale.y * 0.5f;
        dir.y = abs(dir.y);
    }

    // detect score
    if (position.x > window->GetScreenWidth() - (scale.x * 0.5f)) {
        position = vec3(window->GetScreenWidth()*0.5f, window->GetScreenHeight()*0.5f, 0.0f);
        dir = vec2(0.0f);
        world->incrementScore(0);
    }
    if (position.x < scale.x * 0.5f) {
        position = vec3(window->GetScreenWidth()*0.5f, window->GetScreenHeight()*0.5f, 0.0f);
        dir = vec2(0.0f);
        world->incrementScore(1);
    }

    // detect if ball hits left paddle
    Paddle* leftPaddle = world->FindByName<Paddle>("LeftPaddle"); 
    if (EntityOverlap2D(*this ,*leftPaddle)) {
        dir.x = abs(dir.x);
        if(!world->close){
            color = glm::vec4(0.5,    0.5,   2,   1);
        }
    }

    // detect if ball hits right paddle
    Paddle* rightPaddle = world->FindByName<Paddle>("RightPaddle"); 
    if (EntityOverlap2D(*this ,*rightPaddle)) {
        dir.x = abs(dir.x) * -1.0f;
        if(!world->close){
            color = glm::vec4(2,    0.5,   0.5,   1);
        }
    }

    if (dir != vec2(0.0f))
        position += vec3(dir.x, dir.y, 0.0f) * speed * _dt;
}

void Ball::Draw() {mat4 transform = mat4(1.0f);
    transform = translate(transform, position);
    transform = glm::scale(transform, scale);

    // set shader variables
    shader.SetVec4("COLOR", color);
    shader.SetMat4("TRANSFORM", transform);
}

void Ball::OnDestroy() {
}