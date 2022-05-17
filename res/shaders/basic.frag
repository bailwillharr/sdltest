#version 330


in vec3 Norm;
in vec2 UV;

out vec4 FragColor;

uniform sampler2D u_Tex;

void main() {

	vec3 dir = vec3(-0.123, 0.4, 0.56);
	vec4 color = vec4(1.0, 1.0, 1.0, 1.0);

    vec3 lighting = max(dot( normalize(Norm), normalize(dir)), 0.0) * vec3(1.0, 1.0, 1.0);

    FragColor = vec4(lighting, 1.0) * texture(u_Tex, UV);

}
