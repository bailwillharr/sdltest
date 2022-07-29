#include "meshgen.hpp"

#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>

#include <iostream>

#include <thread>

std::unique_ptr<resources::Mesh> genSphereMesh(float r, int detail)
{
	using namespace glm;

	std::vector<Vertex> vertices{};

	float angleStep = two_pi<float>() / (float)detail;

	for (int i = 0; i < detail; i++) {
		// theta goes north-to-south
		float theta = i * angleStep;
		float theta2 = theta + angleStep;
		for (int j = 0; j < detail/2; j++) {
			// phi goes west-to-east
			float phi = j * angleStep;
			float phi2 = phi + angleStep;

			vec3 top_left{		r * sin(phi)  * cos(theta),
								r * cos(phi),
								r * sin(phi)  * sin(theta)	};
			vec3 bottom_left{	r * sin(phi)  * cos(theta2),
								r * cos(phi),
								r * sin(phi)  * sin(theta2)	};
			vec3 top_right{		r * sin(phi2) * cos(theta),
								r * cos(phi2),
								r * sin(phi2) * sin(theta)	};
			vec3 bottom_right{	r * sin(phi2) * cos(theta2),
								r * cos(phi2),
								r * sin(phi2) * sin(theta2)	};

			// triangle 1
			vertices.push_back({top_left, {}, {0.0f, 0.0f}});
			vertices.push_back({bottom_left, {}, {0.0f, 1.0f}});
			vertices.push_back({bottom_right, {}, {1.0f, 1.0f}});
			// triangle 2
			vertices.push_back({top_right, {}, {1.0f, 0.0f}});
			vertices.push_back({top_left, {}, {0.0f, 0.0f}});
			vertices.push_back({bottom_right, {}, {1.0f, 1.0f}});

			glm::vec3 vector1 = (vertices.end() - 1)->pos - (vertices.end() - 2)->pos;
			glm::vec3 vector2 = (vertices.end() - 2)->pos - (vertices.end() - 3)->pos;
			glm::vec3 norm = glm::normalize(glm::cross(vector1, vector2));


			// TODO: FIX NORMALS
			norm = -norm;

			for (auto it = vertices.end() - 6; it != vertices.end(); it++) {
				it->norm = norm;
			}

		}
	}

	return std::make_unique<resources::Mesh>(vertices);
}
