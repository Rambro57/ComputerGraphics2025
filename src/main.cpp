#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <SDL.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Canis/Canis.hpp"
#include "Canis/IOManager.hpp"
#include "Canis/FrameRateManager.hpp"

#include "Entity.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Trail.hpp"
#include "Background.hpp"  // Added background include

//Test

// git restore .
// git fetch
// git pull

// move out to external class
unsigned int vertexShader;
unsigned int VBO, VAO, EBO;
bool ballColorRed;
int timeToClose = 500;

void InitModel();

#ifdef _WIN32
#define main SDL_main
extern "C" int main(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    Canis::Init();

    Canis::Window window;
    window.Create("Computer Graphics 2025", 640, 640, 0);

    Canis::InputManager inputManager;
    Canis::FrameRateManager frameRateManager;
    frameRateManager.Init(60.0f);
    float deltaTime = 0.0f;
    float fps = 0.0f;
    ballColorRed = false;

    Canis::Shader spriteShader;
    spriteShader.Compile("assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
    spriteShader.AddAttribute("aPos");
    spriteShader.AddAttribute("aUV");
    spriteShader.Link();

    // Create background shader
    Canis::Shader backgroundShader;
    backgroundShader.Compile("assets/shaders/background.vs", "assets/shaders/background.fs");
    backgroundShader.AddAttribute("aPos");
    backgroundShader.AddAttribute("aUV");
    backgroundShader.Link();

    InitModel();

    Canis::GLTexture texture = Canis::LoadImageGL("assets/textures/LaserBallSprite.png", true);
    Canis::GLTexture texture2 = Canis::LoadImageGL("assets/textures/LightsaberSprite.png", true);
    Canis::GLTexture bgTexture = Canis::LoadImageGL("assets/textures/background.png", true);  // Load background texture

    int textureSlots = 1;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureSlots);

    Canis::Log(std::to_string(textureSlots));

    spriteShader.SetInt("texture1", 0);
    backgroundShader.SetInt("texture1", 0);  // Set texture slot for background shader

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    World world;
    world.VAO = VAO;
    world.window = &window;
    world.inputManager = &inputManager;

    // Create background
    Background *background = world.Instantiate<Background>();
    background->shader = backgroundShader;
    background->texture = bgTexture;
    background->color = glm::vec4(1, 1, 1, 1);
    
    Ball *ball = world.Instantiate<Ball>();
    ball->shader = spriteShader;
    ball->texture = texture;
    ball->color = glm::vec4(1,1,1,1);
    

    {
        Paddle *paddle = world.Instantiate<Paddle>();
        paddle->shader = spriteShader;
        paddle->texture = texture2;
        paddle->name = "RightPaddle";
        paddle->color = glm::vec4(2,    0.5,   0.5,   1);
        paddle->position = glm::vec3(window.GetScreenWidth() - (10.0f*0.5f), window.GetScreenHeight() * 0.5f, 0.0f);
    }

    {
        Paddle *paddle = world.Instantiate<Paddle>();
        paddle->shader = spriteShader;
        paddle->texture = texture2;
        paddle->name = "LeftPaddle";
        paddle->color = glm::vec4(0.5,  0.5,   2,  1);
        paddle->position = glm::vec3(10.0f*0.5f, window.GetScreenHeight() * 0.5f, 0.0f);
    }

    while (inputManager.Update(window.GetScreenWidth(), window.GetScreenHeight()))
    {
        if(world.close){
            timeToClose--;
            if(timeToClose <= 0){ return 0; }
            if(timeToClose%20==0){
                Ball *ballRain = world.Instantiate<Ball>();
                ballRain->shader = spriteShader;
                ballRain->texture = texture;
                ballRain->speed = 250.0f;
                if(world.victoryColor == 1){
                    ballRain->color = glm::vec4(0.5,    0.5,   2,   1);
                    ball->color = glm::vec4(0.5,    0.5,   2,   1);
                }
                else if(world.victoryColor == 2){
                    ballRain->color = glm::vec4(2,    0.5,   0.5,   1);
                    ball->color = glm::vec4(2,    0.5,   0.5,   1);
                }
            }
            
        }

        Trail *trail = world.Instantiate<Trail>();
            trail->shader = spriteShader;
            trail->texture = texture;
            trail->position = ball->position;
            trail->color = ball->color;
        deltaTime = frameRateManager.StartFrame();
        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        using namespace glm;

        mat4 projection = ortho(0.0f, (float)window.GetScreenWidth(), 0.0f, (float)window.GetScreenHeight(), 0.001f, 100.0f);
        
        mat4 view = mat4(1.0f);
        view = translate(view, vec3(0.0f, 0.0f, 0.5f));
        view = inverse(view);

        world.Update(view, projection, deltaTime);

        window.SwapBuffer();

        fps = frameRateManager.EndFrame();
        
        if(SDL_GetTicks()%60==0){
            std::cout << "FPS: " << fps << std::endl;
        }
    }

    return 0;
}

void InitModel()
{
    float vertices[] = {
        // position         // uv
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  // top left
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}