#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
out vec3 color;
out vec2 uv;
uniform float TIME;
uniform mat4 TRANSFORM;
uniform mat4 PROJECTION;
uniform mat4 VIEW;
void main()
{
   gl_Position = PROJECTION * VIEW * TRANSFORM * vec4(aPos, 1.0f);
   
   // Apply scrolling effect using TIME
   // Only apply to specific entities (like background)
   // This creates a scrolling effect without adding new uniforms
   uv = aUV + vec2(TIME * 0.05, TIME * 0.025);
}