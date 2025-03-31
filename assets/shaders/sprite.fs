#version 330 core
out vec4 FragColor;
in vec3 color;
in vec2 uv;
uniform vec4 COLOR;
uniform float TIME;
uniform sampler2D texture1;
void main()
{
   FragColor = texture(texture1, uv);//COLOR;//vec4(vec3(cos(TIME)), 1.0f);
   FragColor *= vec4(COLOR.x, COLOR.y, COLOR.z, 1.0f);
   //FragColor = color;
}