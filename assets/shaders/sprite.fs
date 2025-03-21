#version 330 core
out vec4 FragColor;
in vec2 uv;
uniform sampler2D texture1;
uniform float TIME;
uniform vec4 COLOR = vec4(1.0, 1.0, 1.0, 1.0);

void main()
{
    vec2 finalUV = uv;
    
    // Only apply scrolling effect to the background (z < -1.0)
    // We can detect the background using gl_FragCoord.z
    if (gl_FragCoord.z > 0.9) {
        // Apply scrolling effect only to background
        finalUV.x = uv.x + TIME * 0.05;
        finalUV.y = uv.y + TIME * 0.02;
        // Wrap coordinates for continuous scrolling
        finalUV = fract(finalUV);
    }
    
    // Sample the texture with either original or scrolled coordinates
    vec4 texColor = texture(texture1, finalUV);
    
    // Apply the COLOR uniform
    FragColor = texColor * COLOR;
}