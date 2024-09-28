#version 410 core

out vec4 FragColor;
in vec2 texCoord;

uniform vec4 ourColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

float near = 0.1;
float far = 10.0;

float LinearDeepth(float z)
{
    float z_n = z * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z_n * (far - near));
}

void main()
{
    //FragColor = mix(texture(texture1, texCoord),texture(texture2, texCoord), 0.7);
    FragColor = vec4(ourColor);

    //float depth = LinearDeepth(gl_FragCoord.z) / far;
    //FragColor = vec4(vec3(depth), 1.0);

}
