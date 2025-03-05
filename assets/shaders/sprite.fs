#version 330 core
out vec4 FragColor;
in vec3 color;
uniform vec4 COLOR;
uniform float TIME;
uniform sampler2D texture1;
void main()
{
   FragColor = texture(texture1, color.xy);//COLOR;//vec4(vec3(cos(TIME)), 1.0f);
}