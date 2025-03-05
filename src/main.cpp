#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>

#include <SDL.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Canis/Canis.hpp"
#include "Canis/Debug.hpp"
#include "Canis/Shader.hpp"
#include "Canis/Window.hpp"
#include "Canis/InputManager.hpp"
#include "Canis/IOManager.hpp"

// git restore .
// git fetch
// git pull

// move out to external class
unsigned int vertexShader;
unsigned int VBO, VAO;

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

    Canis::Shader spriteShader;
    spriteShader.Compile("assets/shaders/sprite.vs", "assets/shaders/sprite.fs");
    spriteShader.AddAttribute("aPos");
    spriteShader.Link();

    InitModel();

    Canis::GLTexture texture = Canis::LoadImageGL("assets/textures/ForcePush.png", true);

    int textureSlots = 0;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureSlots);

    Canis::Log(std::to_string(textureSlots));

    spriteShader.SetInt("texture1", 0);

    glActiveTexture(GL_TEXTURE0+0);
    glBindTexture(GL_TEXTURE_2D, texture.id);    

    while (inputManager.Update(window.GetScreenWidth(), window.GetScreenHeight()))
    {

        glClearColor(
            inputManager.mouse.x / window.GetScreenWidth(),
            inputManager.mouse.y / window.GetScreenHeight(),
            sin((float)SDL_GetTicks() / 1000.0f), 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        // draw first triangle
        spriteShader.Use();
        spriteShader.SetVec4("COLOR", 1.0f, 1.0f, 1.0f, 1.0f);
        spriteShader.SetFloat("TIME", SDL_GetTicks() / 1000.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        spriteShader.UnUse();

        // Canis::Log("Mouse Pos: " + glm::to_string(mousePos));
        window.SwapBuffer();
    }

    return 0;
}

void InitModel()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f, // bottom right
        0.0f, 0.5f, 0.0f // top center
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}