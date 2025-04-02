#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4 COLOR;

void main()
{
    // Sample texture with wrapped coordinates for seamless scrolling
    vec4 texColor = texture(texture1, fract(TexCoord));
    FragColor = texColor * COLOR;
}