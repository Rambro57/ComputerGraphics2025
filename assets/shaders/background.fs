#version 330 core
out vec4 FragColor;
in vec2 uv;
uniform sampler2D texture1;
uniform float TIME;
uniform vec4 COLOR = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
    // Calculate scrolling UV coordinates for background
    vec2 scrolledUV = uv;
    
    // Apply scrolling effect - adjust speeds here
    scrolledUV.x = fract(uv.x + TIME * 0.05);
    scrolledUV.y = fract(uv.y + TIME * 0.03);
    
    // Sample the texture with scrolled coordinates
    vec4 texColor = texture(texture1, scrolledUV);
    FragColor = texColor * COLOR;
}