#version 330

uniform vec3 color;

in vec3 f_Position;

out vec4 FragColor;

void main() {

	FragColor = vec4(color, 1.0);

}
