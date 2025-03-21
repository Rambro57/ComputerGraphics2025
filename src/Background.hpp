#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Canis/Shader.hpp"
#include "Entity.hpp"

class Background : public Entity
{
public:
    Background() : Entity()
    {
        name = "Background";
    }

    virtual void Start() override
    {
        // Position at center of screen with z=-5.0 (behind everything)
        position = glm::vec3(
            world->window->GetScreenWidth() * 0.5f,
            world->window->GetScreenHeight() * 0.5f,
            -5.0f);
    }

    virtual void Update(float deltaTime) override
    {
        // No movement needed, scrolling happens in shader
    }

    virtual void Draw() override
    {
    // Calculate model matrix (position and scale)
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position); // This includes the z=-5.0 position
            model = glm::scale(model, glm::vec3(
            world->window->GetScreenWidth(),
            world->window->GetScreenHeight(),
            1.0f));
        
    // Set up shader
        shader.Use();
    
    // Set the model matrix
         shader.SetMat4("TRANSFORM", model);
    
    // Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.id);
    
    // Note: The actual drawing is done in World::Update
    // You don't need to call glDrawElements here
    }
};

#endif // BACKGROUND_HPP 