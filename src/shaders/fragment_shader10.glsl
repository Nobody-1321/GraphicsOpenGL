#version 410 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D texture1;

void main()
{
    //FragColor = texture(texture1, texCoord);
    vec4 texColor = texture(texture1, texCoord);
    
    if(texColor.a < 0.1)
        discard;
    
    FragColor = texColor;
}
