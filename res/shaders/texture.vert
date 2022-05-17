#version 330

layout (location = 0) in vec3 v_Position;
//layout (location = 1) in vec3 v_Normal;
//layout (location = 2) in vec2 v_UV;

uniform mat4 model;

//out vec3 f_Norm;
//out vec2 f_UV;
  
void main()
{
    gl_Position = model * vec4(v_Position, 1.0);
    //f_Norm = v_Normal;
    //f_UV = v_UV;
}
