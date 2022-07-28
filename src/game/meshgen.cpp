#include "meshgen.hpp"

#include <glm/gtc/constants.hpp>

#include <iostream>

std::unique_ptr<resources::Mesh> genSphereMesh(float r, int detail)
{
	std::vector<Vertex> vertices{};

	for (int i = 0; i < detail; i++) {
		// theta goes west-to-east
		float theta = glm::two_pi<float>() * i / detail;
		for (int j = 0; j < detail; j++) {
			// phi goes south-to-north
			float phi = glm::two_pi<float>() * j / detail;

			vertices.push_back({{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
		}
	}

	return std::make_unique<resources::Mesh>(vertices);
}
