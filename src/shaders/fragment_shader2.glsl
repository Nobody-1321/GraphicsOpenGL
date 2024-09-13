#version 410 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D ourTextuere;

void main()
{
    FragColor = texture(ourTextuere, texCoord);
}
