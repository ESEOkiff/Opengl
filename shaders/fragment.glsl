#version 330 core

out vec4 FragColor;


void main()
{
    // Couleurs basées sur la position et le temps
    float r = 0.75;
    float g = 0.4;
    float b = 0.0;
    
    FragColor = vec4(r, g, b, 1.0);
}