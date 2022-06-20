#version 330

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 f_texCoords;

uniform mat4 projMat;
