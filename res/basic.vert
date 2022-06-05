#version 330

layout (location = 0) in vec3 v_Position;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(v_Position, 1.0);
}
