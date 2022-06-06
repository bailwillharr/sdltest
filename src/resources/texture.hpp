#pragma once

#include "resource.hpp"

#include <glad/glad.h>

namespace resources {

class Texture : public Resource {

private:

	GLuint m_texture;


public:
	Texture(const std::filesystem::path& resPath);
	~Texture() override;

	void bindTexture() const;
};

}
