#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
out vec3 color;
out vec2 uv;
uniform float TIME;
uniform mat4 TRANSFORM;
uniform mat4 PROJECTION;
uniform mat4 VIEW;
uniform vec2 textureOffset = vec2(0.0, 0.0); // Default value if not set

void main()
{
   gl_Position = PROJECTION * VIEW * TRANSFORM * vec4(aPos, 1.0f);
   uv = aUV + textureOffset; // Add texture offset for scrolling effect
}