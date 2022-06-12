#include "resources/texture.hpp"

#include <vector>
#include <iostream>

namespace resources {

// -1 means invalid / no bind
GLuint Texture::s_binded_texture = -1;

Texture::Texture(const std::filesystem::path& resPath) : Resource(resPath, "texture")
{
  	FILE *fp = fopen(resPath.string().c_str(), "rb");
	if (!fp) {
		std::runtime_error("Unable to open texture file");
	}

	fseek(fp, 0x02, SEEK_SET);
	uint64_t tex_data_offset;
	fread(&tex_data_offset, sizeof(uint64_t), 1, fp);

	glGenTextures(1, &m_texture);
	bindTexture(); // glBindTexture
	fseek(fp, 0L, SEEK_END);
	uint64_t end = ftell(fp);

	std::vector<uint8_t> texbuf;
	texbuf.resize(end);
	fseek(fp, tex_data_offset, SEEK_SET);
	fread(texbuf.data(), 1, end, fp);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4096, 4096, 0, GL_RGB, GL_UNSIGNED_BYTE, texbuf.data());

	fclose(fp);

	glGenerateMipmap(GL_TEXTURE_2D); 
}

Texture::~Texture()
{
	if (s_binded_texture == m_texture) {
		s_binded_texture = -1;
	}
}

void Texture::bindTexture() const
{
	if (s_binded_texture != m_texture) {
#ifndef NDEBUG
		std::cerr << "Texture bound\n";
#endif
		glBindTexture(GL_TEXTURE_2D, m_texture);
		s_binded_texture = m_texture;
	}
}

}
