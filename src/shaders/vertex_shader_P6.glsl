#version 430
layout(location = 0) in vec3 pos;

uniform mat4 projection;
uniform mat4 modelView;

void main(void) {
    gl_Position = projection * modelView * vec4(pos, 1.0);
}
