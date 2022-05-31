#version 330

layout (location = 0) in vec3 v_Position;

uniform mat4 modelMat;

void main()
{
    gl_Position = modelMat * vec4(v_Position, 1.0);
}
