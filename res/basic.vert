#version 330

layout (location = 0) in vec3 v_Position;
layout (location = 1) in vec3 v_Norm;
layout (location = 2) in vec2 v_UV;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 f_Norm;
out vec2 f_UV;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(v_Position, 1.0);
    f_Norm = mat3(transpose(inverse(modelMat))) * v_Norm; 
    f_UV = v_UV;
}
