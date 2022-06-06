#version 330

uniform vec3 color;
uniform vec3 lightPos;

in vec3 f_Pos;
in vec3 f_Norm;
in vec2 f_UV;

out vec4 FragColor;

void main() {

	vec3 norm = normalize(f_Norm);
	vec3 lightDir = normalize(lightPos - f_Pos);
	float diff = max(dot(norm, lightDir), 0.0);
	float ambient = 0.2;

	FragColor = vec4((diff + ambient) * vec3(1.0, 1.0, 1.0), 1.0);

}
