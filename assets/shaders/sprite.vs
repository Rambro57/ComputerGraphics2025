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
   //gl_Position = vec4(aPos.x + sin(TIME)*0.5f, aPos.y + cos(TIME)*0.5f, aPos.z, 1.0);
   uv = aUV;
}