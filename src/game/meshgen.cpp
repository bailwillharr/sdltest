#include "meshgen.hpp"

#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>

#include <iostream>

#include <thread>

std::unique_ptr<resources::Mesh> genSphereMesh(float r, int detail)
{
	std::vector<Vertex> vertices{};

	float angleStep = glm::two_pi<float>() / (float)detail;

	for (int i = 0; i < detail; i++) {
		// theta goes north-to-south
		float theta = i * angleStep;
		float theta2 = theta + angleStep;
		for (int j = 0; j < detail/2; j++) {
			// phi goes west-to-east
			float phi = j * angleStep;
			float phi2 = phi + angleStep;

			// triangle 1
			vertices.push_back({{r * glm::cos(phi) * glm::cos(theta), r * glm::sin(theta), r * glm::sin(phi) * glm::cos(theta)}, {}, {0.0f, 0.0f}});
			vertices.push_back({{r * glm::cos(phi) * glm::cos(theta2), r * glm::sin(theta2), r * glm::sin(phi) * glm::cos(theta2)}, {}, {0.0f, 0.0f}});
			vertices.push_back({{r * glm::cos(phi2) * glm::cos(theta), r * glm::sin(theta), r * glm::sin(phi2) * glm::cos(theta)}, {}, {0.0f, 0.0f}});
			// triangle 2
			vertices.push_back({{r * glm::cos(phi) * glm::cos(theta2), r * glm::sin(theta2), r * glm::sin(phi) * glm::cos(theta2)}, {}, {1.0f, 1.0f}});
			vertices.push_back({{r * glm::cos(phi2) * glm::cos(theta2), r * glm::sin(theta2), r * glm::sin(phi2) * glm::cos(theta2)}, {}, {1.0f, 1.0f}});
			vertices.push_back({{r * glm::cos(phi2) * glm::cos(theta), r * glm::sin(theta), r * glm::sin(phi2) * glm::cos(theta)}, {}, {1.0f, 1.0f}});

			glm::vec3 vector1 = (vertices.end() - 1)->pos - (vertices.end() - 2)->pos;
			glm::vec3 vector2 = (vertices.end() - 2)->pos - (vertices.end() - 3)->pos;
			glm::vec3 norm = glm::normalize(glm::cross(vector1, vector2));

			for (auto it = vertices.end() - 6; it != vertices.end(); it++) {
				it->norm = norm;
			}

		}
	}

	return std::make_unique<resources::Mesh>(vertices);
}
