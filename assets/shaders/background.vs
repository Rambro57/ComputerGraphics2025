#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 TexCoord;

uniform mat4 TRANSFORM;
uniform mat4 VIEW;
uniform mat4 PROJECTION;
uniform float offsetX;
uniform float offsetY;

void main()
{
    gl_Position = PROJECTION * VIEW * TRANSFORM * vec4(aPos, 1.0);
    // Apply scrolling offset to texture coordinates for top-right movement
    TexCoord = aUV + vec2(offsetX, offsetY);
}