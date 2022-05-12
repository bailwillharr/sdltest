#version 330

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_UV;

uniform mat4 u_P;
uniform mat4 u_V;

out vec3 Norm;
out vec2 UV;
  
void main()
{
    gl_Position = u_P * u_V * vec4(a_Position, 1.0);
    Norm = a_Normal;
    UV = a_UV;
}
