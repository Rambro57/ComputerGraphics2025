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
#include "Background.hpp"

// git restore .
// git fetch
// git pull

// move out to external class
unsigned int vertexShader;
unsigned int VBO, VAO, EBO;

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

    // Enable depth testing - most important for z-ordering
    glEnable(GL_DEPTH_TEST);

    Canis::InputManager inputManager;
    Canis::FrameRateManager frameRateManager;
    frameRateManager.Init(60.0f);
    float deltaTime = 0.0f;
    float fps = 0.0f;

    // Regular sprite shader for game objects
    Canis::Shader spriteShader;
    spriteShader.Compile("assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
    spriteShader.AddAttribute("aPos");
    spriteShader.AddAttribute("aUV");
    spriteShader.Link();
    spriteShader.SetInt("texture1", 0);

    // Background-specific shader for scrolling effect
    Canis::Shader backgroundShader;
    backgroundShader.Compile("assets/shaders/background.vs", "assets/shaders/background.fs");
    backgroundShader.AddAttribute("aPos");
    backgroundShader.AddAttribute("aUV");
    backgroundShader.Link();
    backgroundShader.SetInt("texture1", 0);

    InitModel();

    Canis::GLTexture gameTexture = Canis::LoadImageGL("assets/textures/ForcePush.png", true);
    Canis::GLTexture backgroundTexture = Canis::LoadImageGL("assets/textures/stars.png", true);
    Canis::GLTexture blankTexture;
    blankTexture.id = 0; // This will effectively use no texture
    Canis::GLTexture texture2 = Canis::LoadImageGL("assets/textures/LightsaberSprite.png", true);

    int textureSlots = 1;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureSlots);
    Canis::Log(std::to_string(textureSlots));

    World world;
    world.VAO = VAO;
    world.window = &window;
    world.inputManager = &inputManager;

    // Create background with z-position behind everything else
    Background *background = world.Instantiate<Background>();
    background->shader = backgroundShader;  // Use background-specific shader
    background->texture = backgroundTexture;
    background->position.z = -5.0f;  // Put it far behind other elements
    background->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // Full brightness

    // Create ball with default z-position of 0
    Ball *ball = world.Instantiate<Ball>();
    ball->shader = spriteShader;
    ball->texture = gameTexture;
    ball->position.z = 0.0f;
    ball->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // Full brightness

    // Create paddles with default z-position of 0 and no texture (just color)
    {
        Paddle *paddle = world.Instantiate<Paddle>();
        paddle->shader = spriteShader;
        paddle->texture = texture2;
        paddle->name = "RightPaddle";
        paddle->position = glm::vec3(window.GetScreenWidth() - (10.0f*0.5f), window.GetScreenHeight() * 0.5f, 0.0f);
        paddle->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // White color
    }

    {
        Paddle *paddle = world.Instantiate<Paddle>();
        paddle->shader = spriteShader;
        paddle->texture = texture2;
        paddle->name = "LeftPaddle";
        paddle->position = glm::vec3(10.0f*0.5f, window.GetScreenHeight() * 0.5f, 0.0f);
        paddle->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);  // White color
    }

    while (inputManager.Update(window.GetScreenWidth(), window.GetScreenHeight()) && !world.close)
    {
        Trail *trail = world.Instantiate<Trail>();
            trail->shader = spriteShader;
            trail->texture = texture;
            trail->position = ball->position;
        deltaTime = frameRateManager.StartFrame();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear depth buffer too

        using namespace glm;

        // Set up a proper projection with depth range
        mat4 projection = ortho(0.0f, (float)window.GetScreenWidth(), 0.0f, (float)window.GetScreenHeight(), -10.0f, 10.0f);
        
        mat4 view = mat4(1.0f);
        view = translate(view, vec3(0.0f, 0.0f, 0.5f));
        view = inverse(view);

        // Update TIME uniform for all shaders
        float currentTime = SDL_GetTicks() / 1000.0f;
        
        // Set time for background shader
        backgroundShader.Use();
        backgroundShader.SetFloat("TIME", currentTime);
        backgroundShader.UnUse();
        
        // Set time for sprite shader
        spriteShader.Use();
        spriteShader.SetFloat("TIME", currentTime);
        spriteShader.UnUse();

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